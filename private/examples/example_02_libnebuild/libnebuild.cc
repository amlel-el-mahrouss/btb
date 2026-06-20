// SPDX-License-Identifier: BSD-3-Clause
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-app-eu/bld

#include <BldKit/JSONManifestBuilder.h>

int main(int argc, char** argv) {
#ifndef _WIN32
  constexpr auto path = "./posix.json";
#else
  constexpr auto path = ".\\win64.json";
#endif

  BldKit::JSONManifestBuilder builder;
  BldKit::BuildConfig         config;

  config.path_    = path;
  config.dry_run_ = false;

  return builder.BuildTarget(config);
}
