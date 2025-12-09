#include <NeBuildKit/JSONManifestBuilder.h>

int main(int argc, char** argv) {
#ifndef _WIN32
  constexpr auto path = "./posix.json";
#else
  constexpr auto path = ".\\win64.json";
#endif

  NeBuild::JSONManifestBuilder builder;
  NeBuild::BuildConfig         config;

  config.path_    = path;
  config.dry_run_ = false;

  return builder.BuildTarget(config);
}
