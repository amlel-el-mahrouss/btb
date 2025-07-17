
// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, all rights reserved.
// ============================================================= //

#include <BuildKit/Includes.h>
#include <BuildKit/JSONManifestBuilder.h>

static bool kFailed = false;
static bool kDryRun = false;

int main(int argc, char** argv) {
  if (argc <= 1) return EXIT_FAILURE;

  for (size_t index = 1; index < argc; ++index) {
    std::string index_path = argv[index];

    if (index_path == "-v" || index_path == "--version") {
      BTB::Logger::info() << "Brought to you by Amlal El Mahrouss for the NeKernel project.\n";
      BTB::Logger::info() << "© 2024-2025 Amlal El Mahrouss, all rights reserved.\n";

      BTB::Logger::info()
          << "Bugs, issues? Check out: https://github.com/nekernel-org/nebuild/issues\n";

      return EXIT_SUCCESS;
    } else if (index_path == "--dry-run") {
      kDryRun = true;
      continue;
    } else if (index_path == "-h" || index_path == "--help") {
      BTB::Logger::info() << "Usage: nebuild <file>\n";

      return EXIT_SUCCESS;
    }

    if (index_path.starts_with("-")) {
      BTB::Logger::info() << "error: unknown option '" << index_path << "'\n";

      return EXIT_FAILURE;
    }

    std::thread job_build_thread(
        [](std::string index_path) -> void {
          BTB::IManifestBuilder* builder = nullptr;

          const auto kJsonExtension = ".json";

          if (index_path.ends_with(kJsonExtension)) {
            builder = new BTB::JSONManifestBuilder();

            if (!builder) {
              kFailed = true;
              return;
            }
          } else {
            BTB::Logger::info() << "error: file '" << index_path << "' is not a JSON file!"
                                << std::endl;
            kFailed = true;
            return;
          }

          BTB::Logger::info() << "building manifest: " << index_path << std::endl;

          if (builder && !builder->buildTarget(index_path.size(), index_path.c_str(), kDryRun)) {
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
