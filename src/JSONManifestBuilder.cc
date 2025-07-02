// ============================================================= //
// btb
// Copyright (C) 2024-2025, Amlal El Mahrouss, all rights reserved.
// ============================================================= //

#include <BTBKit/JSONManifestBuilder.h>

using String = std::string;
using JSON   = nlohmann::json;
namespace FS = std::filesystem;

using namespace BTB;

/// @brief Builds a JSON target from a JSON file.
/// @param arg_sz filename size (must be 1 or greater).
/// @param arg_val filename path (must be a valid JSON file).
/// @retval true building has succeeded.
/// @retval false fail to build, see error message.
bool JSONManifestBuilder::buildTarget(int arg_sz, const char* arg_val, const bool dry_run) {
  String path;

  if (!arg_val) {
    BTB::Logger::info() << "btb: error: file path is empty" << std::endl;
    return false;
  }

  if (arg_sz < 0) {
    BTB::Logger::info() << "btb: error: file path is empty" << std::endl;
    return false;
  } else {
    path = arg_val;

    if (!FS::exists(path)) {
      BTB::Logger::info() << "btb: error: file '" << path << "' does not exist" << std::endl;
      return false;
    }
  }

  try {
    std::ifstream json(path);

    if (!json.good()) {
      BTB::Logger::info() << "btb: error: file '" << path << "' is not a valid JSON" << std::endl;
      return false;
    }

    JSON json_obj = JSON::parse(json);

    String compiler = json_obj["compiler_path"].get<String>();

    JSON header_search_path = json_obj["headers_path"];
    JSON sources_files      = json_obj["sources_path"];

    String command = compiler + " ";

    for (auto& sources : sources_files) {
      command += sources.get<String>() + " ";
    }

    for (auto& headers : header_search_path) {
      command += "-I" + headers.get<String>() + " ";
    }

    JSON macros_list = json_obj["cpp_macros"];

    for (auto& macro : macros_list) {
      command += "-D" + macro.get<String>() + " ";
    }

    JSON compiler_flags = json_obj["compiler_flags"];

    for (auto& flag : compiler_flags) {
      command += flag.get<String>() + " ";
    }

    if (json_obj["compiler_std"].is_string())
      command += "-std=" + json_obj["compiler_std"].get<String>() + " ";

    command += "-o " + json_obj["output_name"].get<String>();

    auto target = json_obj["output_name"].get<String>();

    BTB::Logger::info() << "output path: " << target << "\n";
    BTB::Logger::info() << "command: " << command << "\n";

    try {
      if (json_obj["dry_run"].get<bool>()) return true;
    } catch (...) {
    }

    if (dry_run) {
      return true;
    }

    auto ret_exec = std::system(command.c_str());

    if (ret_exec > 0) {
      BTB::Logger::info() << "error: exit with message: " << std::strerror(ret_exec) << "" << std::endl;
      return false;
    }

    try {
      if (json_obj["run_after_build"].get<bool>()) {
        if (target.ends_with(".so")) {
          BTB::Logger::info() << "error: can't open dynamic library, it mayn't have an entrypoint"
                              << std::endl;

          return true;
        } else if (target.ends_with(".dylib") || target.ends_with(".dll")) {
          std::ifstream     file = std::ifstream(target);
          std::stringstream ss;

          ss << file.rdbuf();

          if (ss.str()[0] == 'J' && ss.str()[1] == 'o' && ss.str()[2] == 'y' && ss.str()[3] == '!')
            BTB::Logger::info()
                << "error: can't open PEF dynamic library, it mayn't contain an entrypoint"
                << std::endl;
          else if (ss.str()[0] == '!' && ss.str()[1] == 'y' && ss.str()[2] == 'o' &&
                   ss.str()[3] == 'J')
            BTB::Logger::info()
                << "error: can't open FEP dynamic library, it mayn't contain an entrypoint"
                << std::endl;
          else if (ss.str()[0] == 'M' && ss.str()[1] == 'Z')
            BTB::Logger::info()
                << "error: can't open MZ dynamic library, it mayn't contain an entrypoint"
                << std::endl;
          else if (ss.str()[0] == 0x7F && ss.str()[1] == 'E') {
            BTB::Logger::info()
                << "error: can't open ELF dynamic library, it mayn't contain an entrypoint"
                << std::endl;
          }

          return true;
        }

#if defined(BTB_WINDOWS)
        std::system((".\\" + target).c_str());
#else
        std::system(("./" + target).c_str());
#endif
      }
    } catch (...) {
      return true;
    }
  } catch (std::runtime_error& err) {
    BTB::Logger::info() << "error: " << err.what() << std::endl;

    return false;
  }

  return true;
}

const char* JSONManifestBuilder::buildSystem() {
  return "json";
}
