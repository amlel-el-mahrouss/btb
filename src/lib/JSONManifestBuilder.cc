// ============================================================= //
// NeBuild
// PURPOSE: JSON support.
// Copyright (C) 2024-2025, Amlal El Mahrouss and NeKernel Authors, licensed under BSD-3 license.
// ============================================================= //

#include <NeBuildKit/JSONManifestBuilder.h>
#include <json/json.h>
#include <fstream>

namespace NeBuild {
namespace FS = std::filesystem;

/// =========================================================== ///
/// @brief Builds a nlohmann::json target from a nlohmann::json file.
/// @param arg_sz filename size (must be 1 or greater).
/// @param arg_val filename path (must be a valid nlohmann::json file).
/// @return bool: whether the build has succeeded or not.
/// =========================================================== ///
bool JSONManifestBuilder::BuildTarget(BuildConfig& config) {
  std::string path;

  if (config.path_.empty()) {
    NeBuild::Logger::info() << "nebuild: error: file path is empty" << std::endl;
    return false;
  } else {
    path = config.path_;

    if (!FS::exists(path)) {
      NeBuild::Logger::info() << "nebuild: error: file '" << path << "' does not exist"
                              << std::endl;
      return false;
    }
  }

  try {
    std::ifstream json(path);

    if (!json.good()) {
      NeBuild::Logger::info() << "nebuild: error: file '" << path
                              << "' is not a valid nlohmann::json" << std::endl;
      return false;
    }

    nlohmann::json json_obj = nlohmann::json::parse(json);

    try {
      nlohmann::json description = json_obj["description"];

      NeBuild::Logger::info() << "nebuild: installing: " << path << std::endl;

      if (auto res = description.get<std::string>(); !res.empty())
        NeBuild::Logger::info() << "nebuild: description: " << res << std::endl;
    } catch (...) {
      
    }

    std::string compiler = json_obj["compiler_path"].get<std::string>();

    std::string command = compiler + " ";

    nlohmann::json header_search_path = json_obj["compiler_headers_path"];

    for (auto& headers : header_search_path) {
      command += "-I" + headers.get<std::string>() + " ";
    }

    nlohmann::json headers_path = json_obj["headers_path"];

    for (auto& headers : headers_path) {
      command += "-I" + headers.get<std::string>() + " ";
    }

    nlohmann::json sources_files = json_obj["sources_path"];

    for (auto& sources : sources_files) {
      command += sources.get<std::string>() + " ";
    }

    nlohmann::json macros_list = json_obj["cpp_macros"];

    for (auto& macro : macros_list) {
      command += "-D" + macro.get<std::string>() + " ";
    }

    nlohmann::json compiler_flags = json_obj["compiler_flags"];

    for (auto& flag : compiler_flags) {
      command += flag.get<std::string>() + " ";
    }

    if (json_obj["compiler_std"].is_string())
      command += "-std=" + json_obj["compiler_std"].get<std::string>() + " ";

    command += "-o " + json_obj["output_name"].get<std::string>();

    auto target = json_obj["output_name"].get<std::string>();

    NeBuild::Logger::info() << "output path: " << target << "\n";

    auto ret_exec = std::system(command.c_str());

    if (ret_exec > 0) {
      NeBuild::Logger::info() << "error: exit with message: " << std::strerror(ret_exec) << ""
                              << std::endl;
      config.has_failed_ = true;
      return false;
    }
  } catch (const std::exception& err) {
    NeBuild::Logger::info() << "error: exit with message: " << err.what() << "" << std::endl;
    config.has_failed_ = true;
    return false;
  }

  return true;
}

/// =========================================================== ///
/// @brief Returns the build system name.
/// =========================================================== ///
const std::string_view JSONManifestBuilder::BuildSystem() {
  return "NeBuild (nlohmann::json)";
}
}  // namespace NeBuild
