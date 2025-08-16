#include <BuildKit/JSONManifestBuilder.h>
#include <cstdlib>

#ifndef _WIN32
static auto kPath = "./posix.json";
#else
static auto kPath = ".\\win64.json";
#endif

int main(int argc, char** argv) {
  auto builder = new NeBuild::JSONManifestBuilder();
  if (!builder) return EXIT_FAILURE;

  return builder->BuildTarget(kPath);
}
