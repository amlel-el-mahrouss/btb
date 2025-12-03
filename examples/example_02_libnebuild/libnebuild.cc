#include <NeBuildKit/JSONManifestBuilder.h>

int main(int argc, char** argv) {
#ifndef _WIN32
  constexpr auto kPath = "./posix.json";
#else
  constexpr auto kPath = ".\\win64.json";
#endif

  NeBuild::JSONManifestBuilder builder;
  NeBuild::BuildConfig         config;

  config.path_    = kPath;
  config.dry_run_ = false;

  return builder.BuildTarget(config);
}
