#include <NeBuildKit/JSONManifestBuilder.h>
#include <cstdlib>

#ifndef _WIN32
static constexpr auto kPath = "./posix.json";
#else
static constexpr auto kPath = ".\\win64.json";
#endif

int main(int argc, char** argv) {
  auto builder = new NeBuild::JSONManifestBuilder();
  if (!builder) return EXIT_FAILURE;

  NeBuild::BuildConfig config;
  config.path_ = kPath;
  config.dry_run_ = false;

  return builder->BuildTarget(config);
}
