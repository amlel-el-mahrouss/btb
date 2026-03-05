
// ============================================================= //
// NeBuild
// FILE: main.cc
// PURPOSE: Main Tool Entrypoint.
// Copyright (C) 2024-2025, Amlal El Mahrouss and NeKernel Authors, licensed under BSD-3 license.
// ============================================================= //

#include <NeBuildKit/JSONManifestBuilder.h>
#include <NeBuildKit/TOMLManifestBuilder.h>
#include <memory>
#include <thread>

constexpr auto kNeBuildFileJson = "Jbuild";
constexpr auto kNeBuildFileToml = "Tbuild";

int main(int argc, char** argv) {
  if (argc < 1) return EXIT_FAILURE;

  NeBuild::BuildConfig config;

  for (size_t index = 1; index < argc; ++index) {
    std::string index_path = argv[index];

    if (index_path == "-v" || index_path == "-version") {
      NeBuild::Logger::info() << "NeBuild (" << NEBUILD_VERSION << ")\n";
      return EXIT_SUCCESS;
    } else if (index_path == "-dry-run" || index_path == "-n") {
      config.dry_run(true);
      continue;
    } else if (index_path == "-h" || index_path == "-help") {
      NeBuild::Logger::info() << "nebuild <options> <{Jbuild, Tbuild}/file.{json, toml}>\n";
      return EXIT_SUCCESS;
    }

    auto index_cpy = index;

    std::thread job_build_thread([&index_path, &index, &index_cpy, &argc, &argv, &config]() -> void {
      std::unique_ptr<NeBuild::IManifestBuilder> builder;

      constexpr auto kJsonExtension = ".json";

      if (index_path.ends_with(kJsonExtension) || index_path == kNeBuildFileJson) {
        builder = std::make_unique<NeBuild::JSONManifestBuilder>();

	/// report failed build to config.
        if (!builder) {
          config.has_failed(true);
          return;
        }
      } else {
        constexpr auto kTomlExtension = ".toml";
        builder = std::make_unique<NeBuild::TOMLManifestBuilder>();

        if (!index_path.ends_with(kTomlExtension) && index_path != kNeBuildFileToml) {
          NeBuild::Logger::info() << "error: file '" << index_path << "' is not a manifest file!"
                                  << std::endl;
          config.has_failed(true);
          return;
        }
      }

      std::string next_path;

      if ((index_cpy + 1) < argc && argv[index_cpy + 1]) next_path = argv[index_cpy + 1];

      if (next_path == "-build-system") {
        NeBuild::Logger::info() << builder->BuildSystem() << std::endl;
        std::exit(EXIT_SUCCESS);
      }

      NeBuild::Logger::info() << "building manifest: " << index_path << std::endl;

      config.path(index_path);

      if (builder && !builder->BuildTarget(config)) {
        config.has_failed(true);
      }
    });

    job_build_thread.join();
  }

  // check for whether config is valid. if so return failure, or success.
  return !config ? EXIT_FAILURE : EXIT_SUCCESS;
}
