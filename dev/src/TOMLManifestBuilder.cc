// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, licensed under BSD-3 license.
// ============================================================= //

#include <BuildKit/TOMLManifestBuilder.h>

namespace FS = std::filesystem;

using namespace NeBuild;

/// @brief Builds a TOML target from a TOML file.
/// @param arg_sz filename size (must be 1 or greater).
/// @param arg_val filename path (must be a valid TOML file).
/// @retval true building has succeeded.
/// @retval false fail to build, see error message.
bool TOMLManifestBuilder::BuildTarget(const std::string& argv_val, const bool dry_run) {
  std::string path;

  if (argv_val.empty()) {
    NeBuild::Logger::info() << "nebuild: error: file path is empty" << std::endl;
    return false;
  } else {
    path = argv_val;

    if (!FS::exists(path)) {
      NeBuild::Logger::info() << "nebuild: error: file '" << path << "' does not exist"
                              << std::endl;
      return false;
    }
  }

  try {
    auto toml_file = toml::parse_file(path);

    std::string compiler = toml_file["compiler_path"].as_string()->get();

    std::string command = compiler + " ";

    auto header_search_path = toml_file["compiler_headers_path"].as_array();

    if (header_search_path) {
      for (auto& headers : *header_search_path) {
        command += "-I" + headers.as_string()->get() + " ";
      }
    }

    auto headers_path = toml_file["headers_path"].as_array();

    if (headers_path) {
      for (auto& headers : *headers_path) {
        command += "-I" + headers.as_string()->get() + " ";
      }
    }

    auto sources_files = toml_file["sources_path"].as_array();

    if (sources_files) {
      for (auto& sources : *sources_files) {
        command += sources.as_string()->get() + " ";
      }
    }

    auto macros_list = toml_file["cpp_macros"].as_array();

    if (macros_list) {
      for (auto& macro : *macros_list) {
        command += "-D" + macro.as_string()->get() + " ";
      }
    }

    auto compiler_flags = toml_file["compiler_flags"].as_array();

    if (compiler_flags) {
      for (auto& flag : *compiler_flags) {
        command += flag.as_string()->get() + " ";
      }
    }

    if (toml_file["compiler_std"].is_string())
      command += "-std=" + toml_file["compiler_std"].as_string()->get() + " ";

    command += "-o " + toml_file["output_name"].as_string()->get();

    auto target = toml_file["output_name"].as_string()->get();

    NeBuild::Logger::info() << "output path: " << target << "\n";
    NeBuild::Logger::info() << "command: " << command << "\n";

    auto ret_exec = std::system(command.c_str());

    if (ret_exec > 0) {
      NeBuild::Logger::info() << "error: exit with message: " << std::strerror(ret_exec) << ""
                              << std::endl;
      return false;
    }
  } catch (std::runtime_error& err) {
    NeBuild::Logger::info() << "error: " << err.what() << std::endl;
    return false;
  }

  return true;
}

const char* TOMLManifestBuilder::BuildSystem() {
  return "NeBuild (TOML)";
}
