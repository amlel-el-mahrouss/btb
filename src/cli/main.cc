
// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, licensed under BSD-3 license.
// ============================================================= //

#include <NeBuildKit/JSONManifestBuilder.h>
#include <NeBuildKit/TOMLManifestBuilder.h>
#include <thread>

static NeBuild::BuildConfig kConfig;

int main(int argc, char** argv) {
  if (argc <= 1) return EXIT_FAILURE;

  for (size_t index = 1; index < argc; ++index) {
    std::string index_path = argv[index];

    if (index_path == "-v" || index_path == "-version") {
      NeBuild::Logger::info() << "NeBuild (" << LIBNEBUILD_VERSION << ")\n";
      NeBuild::Logger::info()
          << "Bugs, issues? https://github.com/nekernel-org/nebuild/issues\n";

      return EXIT_SUCCESS;
    } else if (index_path == "-dry-run" || index_path == "-n") {
      kConfig.dry_run_ = true;
      continue;
    } else if (index_path == "-h" || index_path == "-help") {
      NeBuild::Logger::info() << "usage: nebuild <options> <file>.\n";

      return EXIT_SUCCESS;
    }

    auto index_cpy = index;

    std::thread job_build_thread(
        [&index_path, &index, &index_cpy, &argv]() -> void {
          NeBuild::IManifestBuilder* builder = nullptr;

          const auto kJsonExtension = ".json";

          if (index_path.ends_with(kJsonExtension)) {
            builder = new NeBuild::JSONManifestBuilder();

            if (!builder) {
              kConfig.has_failed_ = true;
              return;
            }
          } else {
            const auto kTomlExtension = ".toml";
            builder                   = new NeBuild::TOMLManifestBuilder();

            if (index_path.ends_with(kTomlExtension)) {
              goto nebuild_build_target;
            } else {
              NeBuild::Logger::info()
                  << "error: file '" << index_path << "' is not a manifest file!" << std::endl;
              kConfig.has_failed_ = true;
              return;
            }
          }

        nebuild_build_target:
          std::string next_path;

          if (argv[index_cpy + 1]) next_path = argv[index_cpy + 1];

          if (next_path == "-build-system") {
            NeBuild::Logger::info() << builder->BuildSystem() << std::endl;
            std::exit(EXIT_SUCCESS);
          }

          NeBuild::Logger::info() << "building manifest: " << index_path << std::endl;

          kConfig.path_ = index_path;
          
          if (builder && !builder->BuildTarget(kConfig)) {
            kConfig.has_failed_ = true;
          }

        toml_build_done:
          delete builder;
          builder = nullptr;
        });

    job_build_thread.join();
  }

  return !kConfig ? EXIT_FAILURE : EXIT_SUCCESS;
}
