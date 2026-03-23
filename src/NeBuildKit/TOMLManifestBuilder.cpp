// SPDX-License-Identifier: BSD-3-Clause
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-foss-org/build

#include <NeBuildKit/TOMLManifestBuilder.h>
#include <toml++/toml.hpp>
#include <filesystem>

namespace NeBuild {

namespace FS = std::filesystem;

/// =========================================================== ///
/// @brief Builds a TOML target from a TOML file.
/// @param arg_sz filename size (must be 1 or greater).
/// @param arg_val filename path (must be a valid TOML file).
/// @return bool: whether the build has succeeded or not.
/// =========================================================== ///
bool TOMLManifestBuilder::BuildTarget(BuildConfig& config) {
  std::string path;

  if (config.path_.empty()) {
    NeBuild::Logger::info() << "error: file path is empty" << std::endl;
    return false;
  } else {
    path = config.path_;

    if (!FS::exists(path)) {
      NeBuild::Logger::info() << "error: file '" << path << "' does not exist" << std::endl;
      return false;
    }
  }

  try {
    auto toml_file = toml::parse_file(path);

    try {
      auto* description = toml_file["description"].as_string();

      if (!description) throw std::runtime_error({});

      NeBuild::Logger::info() << "package path: " << path << std::endl;

      if (description)
        NeBuild::Logger::info() << "description: " << description->get() << std::endl;
    } catch (...) {
    }

    auto* compiler_path_ptr = toml_file["compiler_path"].as_string();
    if (!compiler_path_ptr) return false;

    std::string compiler = compiler_path_ptr->get();
    std::string command  = compiler + " ";

    auto* header_search_path_ptr = toml_file["compiler_headers_path"].as_array();
    if (!header_search_path_ptr) return false;

    auto header_search_path = header_search_path_ptr;

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

    if (!toml_file["compiler_std"].is_string()) return false;

    command += "-std=" + toml_file["compiler_std"].as_string()->get() + " ";

    if (toml_file["output_name"].as_string() == nullptr) return false;

    command += "-o " + toml_file["output_name"].as_string()->get();

    auto target = toml_file["output_name"].as_string()->get();

    NeBuild::Logger::info() << "output: " << target << "\n";

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
const std::string_view TOMLManifestBuilder::BuildSystem() {
  return "NeBuild (toml++::toml)";
}

}  // namespace NeBuild
