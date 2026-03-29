// SPDX-License-Identifier: BSD-3-Clause
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-foss-org/build

#include <NeBuildKit/JSONManifestBuilder.h>
#include <NeBuildKit/TOMLManifestBuilder.h>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

int main(int argc, char** argv) {
  if (argc < 1) return EXIT_FAILURE;

  try {
    NeBuild::BuildConfig config;

    std::vector<std::thread> jobs;

    for (size_t index{1}; index < argc; ++index) {
      std::string index_path = argv[index];

      if (index_path == "-v" || index_path == "--version") {
        NeBuild::Logger::info() << "NeBuild (" << NEBUILD_VERSION << ")\n";
        return EXIT_SUCCESS;
      } else if (index_path == "--dry-run" || index_path == "-n") {
        config.dry_run(true);
        continue;
      } else if (index_path == "-h" || index_path == "--help") {
        NeBuild::Logger::info() << "nebuild <options> <{Jbuild, Tbuild}/file.{json, toml}>\n";
        return EXIT_SUCCESS;
      }

      size_t     index_cpy{index};
      std::mutex mutex;

      jobs.push_back(std::thread{
          [&mutex, &index, &index_cpy, &argc, &argv, &config](std::string index_path) -> void {
            std::unique_lock<decltype(mutex)>          lk{mutex};
            std::unique_ptr<NeBuild::IManifestBuilder> builder;

            constexpr auto kJsonExtension = ".json";

            if (index_path.ends_with(kJsonExtension)) {
              builder = std::make_unique<NeBuild::JSONManifestBuilder>();

              /// report failed build to config.
              if (!builder) {
                config.has_failed(true);
                return;
              }
            } else {
              constexpr auto kTomlExtension = ".toml";

              builder                       = std::make_unique<NeBuild::TOMLManifestBuilder>();

              if (!index_path.ends_with(kTomlExtension)) {
                NeBuild::Logger::info()
                    << "error: file '" << index_path << "' is not a manifest file!" << std::endl;
                config.has_failed(true);
                return;
              }
            }

            std::string path;

            if ((index_cpy + 1) < argc && argv[index_cpy + 1]) path = argv[index_cpy + 1];

            if (path == "--build-system" || path == "-B") {
              NeBuild::Logger::info() << builder->BuildSystem() << std::endl;
              std::exit(EXIT_SUCCESS);
            }

            NeBuild::Logger::info() << "building manifest: " << index_path << std::endl;

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
  } catch (...) {
    
  }
}
