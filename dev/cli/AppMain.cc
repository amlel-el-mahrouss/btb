
// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, licensed under BSD-3 license.
// ============================================================= //

#include <BuildKit/JSONManifestBuilder.h>
#include <BuildKit/TOMLManifestBuilder.h>

static bool kFailed = false;
static bool kDryRun = false;

int main(int argc, char** argv) {
  if (argc <= 1) return EXIT_FAILURE;

  for (size_t index = 1; index < argc; ++index) {
    std::string index_path = argv[index];

    if (index_path == "-v" || index_path == "--version") {
      NeBuild::Logger::info() << "NeKernel Build.\n";
      NeBuild::Logger::info()
          << "Bugs or issues? Check out: https://github.com/nekernel-org/nebuild/issues\n";

      return EXIT_SUCCESS;
    } else if (index_path == "--dry-run" || index_path == "-n") {
      kDryRun = true;
      continue;
    } else if (index_path == "-h" || index_path == "--help") {
      NeBuild::Logger::info() << "usage: nebuild <file>\n";

      return EXIT_SUCCESS;
    }

    if (index_path.starts_with("-")) {
      NeBuild::Logger::info() << "error: unknown option '" << index_path << "'\n";

      return EXIT_FAILURE;
    }

    std::thread job_build_thread(
        [](std::string index_path) -> void {
          NeBuild::IManifestBuilder* builder = nullptr;

          const auto kJsonExtension = ".json";

          if (index_path.ends_with(kJsonExtension)) {
            builder = new NeBuild::JSONManifestBuilder();

            if (!builder) {
              kFailed = true;
              return;
            }
          } else {
            const auto kTomlExtension = ".toml";
            builder                   = new NeBuild::TOMLManifestBuilder();

            if (index_path.ends_with(kTomlExtension)) {
              goto end;
            } else {
              NeBuild::Logger::info()
                  << "error: file '" << index_path << "' is not a manifest file!" << std::endl;
              kFailed = true;
              return;
            }
          }

        end:
          NeBuild::Logger::info() << "building manifest: " << index_path << std::endl;

          if (builder && !builder->BuildTarget(index_path, kDryRun)) {
            kFailed = true;
          }

          delete builder;
          builder = nullptr;
        },
        index_path);

    job_build_thread.join();
  }

  return kFailed ? EXIT_FAILURE : EXIT_SUCCESS;
}
