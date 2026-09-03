// SPDX-License-Identifier: BSD-3-Clause
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-app-eu/bld

#include <BldKit/JSONManifestBuilder.h>

#ifndef NEBUILD_WINDOWS
#include <BldKit/TOMLManifestBuilder.h>
#endif

#include <memory>
#include <mutex>
#include <thread>
#include <vector>

struct BuildCommandLine {
  std::vector<std::string> manifest_paths;
  std::size_t              manifest_count{0};

  int operator()(const std::string& index_path, BldKit::BuildConfig& config) {
    if (index_path == "-v" || index_path == "--version") {
      BldKit::Logger::info() << "NeBuild (" << NEBUILD_VERSION << ")\n";
      return EXIT_SUCCESS;
    } else if (index_path == "--dry-run" || index_path == "-n") {
      config.dry_run(true);
      return EXIT_SUCCESS;
    } else if (index_path == "-h" || index_path == "--help") {
      BldKit::Logger::info() << "nebld <options> <{Jbuild, Tbuild}/file.{json, toml}>\n";
      return EXIT_SUCCESS;
    } else if (index_path == "/h" || index_path == "/help") {
      BldKit::Logger::info() << "nebld <options> <{Jbuild, Tbuild}/file.{json, toml}>\n";
      return EXIT_SUCCESS;
    } else if (index_path == "/v" || index_path == "/version") {
      BldKit::Logger::info() << "NeBuild (" << NEBUILD_VERSION << ")\n";
      return EXIT_SUCCESS;
    } else if (index_path == "/dry-run" || index_path == "/n") {
      config.dry_run(true);
      return EXIT_SUCCESS;
    } 

    return EXIT_FAILURE;
  }
};

int main(int argc, char** argv) {
  if (argc < 1) return EXIT_FAILURE;

  try {
    BldKit::BuildConfig config;
    BuildCommandLine    cmdline;

    std::vector<std::thread> jobs;

    for (size_t index{1}; index < argc; ++index) {
      std::string index_path = argv[index];

      /// Handle command line arguments for version, help, and dry-run options.
      if (cmdline(index_path, config) == EXIT_SUCCESS) continue;

      cmdline.manifest_paths.push_back(index_path);
      cmdline.manifest_count++;
    }

    if (cmdline.manifest_count == 0) {
      BldKit::Logger::info() << "error: no manifest file provided!" << std::endl;
      return EXIT_FAILURE;
    }

    size_t index{0};

    for (const auto& index_path : cmdline.manifest_paths) {
      size_t     index_cpy{index};
      std::mutex mutex;

      jobs.push_back(std::thread{
          [&mutex, &index, &index_cpy, &argc, &argv, &config](std::string index_path) -> void {
            std::unique_lock<decltype(mutex)>          lk{mutex};
            std::unique_ptr<BldKit::IManifestBuilder> builder;

            constexpr auto kJsonExtension = ".json";

            if (index_path.ends_with(kJsonExtension)) {
              builder = std::make_unique<BldKit::JSONManifestBuilder>();
            } else {
#ifndef NEBUILD_WINDOWS
              constexpr auto kTomlExtension = ".toml";

              builder                       = std::make_unique<BldKit::TOMLManifestBuilder>();

              if (!index_path.ends_with(kTomlExtension)) {
                BldKit::Logger::info()
                    << "error: file '" << index_path << "' is not a manifest file!" << std::endl;
                config.has_failed(true);
                return;
              }
#else
              BldKit::Logger::info() << "error: file '" << index_path
                                      << "' is not a manifest file! (TOML support is not "
                                         "available on Windows)"
                                      << std::endl;
              config.has_failed(true);
              return;
#endif
            }

            std::string path;

            if ((index_cpy + 1) < argc && argv[index_cpy + 1]) path = argv[index_cpy + 1];

            if (path == "--build-system" || path == "-B") {
              BldKit::Logger::info() << builder->BuildSystem() << std::endl;
              std::exit(EXIT_SUCCESS);
            }

            BldKit::Logger::info() << "building manifest: " << index_path << std::endl;

            config.path(index_path);

            if (builder && !builder->BuildTarget(config)) {
              config.has_failed(true);
            }
          },
          index_path});
    }
    
    for (auto& job : jobs) job.join();

    // check for whether config is valid. if so return failure, or success.
    return !config ? EXIT_FAILURE : EXIT_SUCCESS;
  } catch (const std::runtime_error& err) {
    BldKit::Logger::info() << "error: " << err.what() << std::endl;
  }
}
