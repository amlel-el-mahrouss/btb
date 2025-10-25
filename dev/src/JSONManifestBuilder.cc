// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, all rights reserved.
// ============================================================= //

#include <BuildKit/JSONManifestBuilder.h>

#if defined(NEBUILD_POSIX)
#include <dlfcn.h>
#endif

using JSON   = nlohmann::json;
namespace FS = std::filesystem;

using namespace NeBuild;

/// @brief Builds a JSON target from a JSON file.
/// @param arg_sz filename size (must be 1 or greater).
/// @param arg_val filename path (must be a valid JSON file).
/// @retval true building has succeeded.
/// @retval false fail to build, see error message.
bool JSONManifestBuilder::BuildTarget(const std::string& argv_val, const bool dry_run) {
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
    std::ifstream json(path);

    if (!json.good()) {
      NeBuild::Logger::info() << "nebuild: error: file '" << path << "' is not a valid JSON"
                              << std::endl;
      return false;
    }

    JSON json_obj = JSON::parse(json);

    std::string compiler = json_obj["compiler_path"].get<std::string>();

    if (compiler != "g++" || !compiler.starts_with("clang")) {
      NeBuild::Logger::info() << "nebuild: error: compiler '" << compiler << "' is not a valid C/C++ compiler!"
                              << std::endl;
      return false;
    }

    std::string command = compiler + " ";

    JSON header_search_path = json_obj["compiler_headers_path"];

    for (auto& headers : header_search_path) {
      command += "-I" + headers.get<std::string>() + " ";
    }

    JSON headers_path = json_obj["headers_path"];
    JSON sources_files      = json_obj["sources_path"];

    for (auto& sources : sources_files) {
      command += sources.get<std::string>() + " ";
    }

    JSON macros_list = json_obj["cpp_macros"];

    for (auto& macro : macros_list) {
      command += "-D" + macro.get<std::string>() + " ";
    }

    JSON compiler_flags = json_obj["compiler_flags"];

    for (auto& flag : compiler_flags) {
      command += flag.get<std::string>() + " ";
    }

    if (json_obj["compiler_std"].is_string())
      command += "-std=" + json_obj["compiler_std"].get<std::string>() + " ";

    command += "-o " + json_obj["output_name"].get<std::string>();

    auto target = json_obj["output_name"].get<std::string>();

    NeBuild::Logger::info() << "output path: " << target << "\n";
    NeBuild::Logger::info() << "command: " << command << "\n";

    try {
      if (json_obj["dry_run"].get<bool>()) return true;
    } catch (...) {
    }

    if (dry_run) {
      return true;
    }

    auto ret_exec = std::system(command.c_str());

    if (ret_exec > 0) {
      NeBuild::Logger::info() << "error: exit with message: " << std::strerror(ret_exec) << ""
                              << std::endl;
      return false;
    }

    try {
      if (json_obj["run_after_build"].get<bool>()) {
        if (target.ends_with(".so") || target.ends_with(".dylib")) {
#if defined(NEBUILD_POSIX)
          auto dll = dlopen(target.c_str(), RTLD_LAZY);

          if (dll) {
            int (*entrypoint)(void) = nullptr;
            entrypoint              = (decltype(entrypoint)) dlsym(dll, "shared_runner");

            if (entrypoint) entrypoint();

            dlclose(dll);

            return true;
          }
#endif

          return false;
        } else {
          return false;
        }

#if defined(NEBUILD_WINDOWS)
        std::system((".\\" + target).c_str());
#else
        std::system(("./" + target).c_str());
#endif
      }
    } catch (...) {
      return true;
    }
  } catch (std::runtime_error& err) {
    NeBuild::Logger::info() << "error: " << err.what() << std::endl;

    return false;
  }

  return true;
}

const char* JSONManifestBuilder::BuildSystem() {
  return "NeBuild (JSON)";
}
