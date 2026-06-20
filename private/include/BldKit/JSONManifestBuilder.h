// SPDX-License-Identifier: BSD-3-Clause
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-app-eu/bld

#pragma once

#include <BldKit/IManifestBuilder.h>

/// @file JSONManifestBuilder.h
/// @brief JSON manifest builder header file.

namespace BldKit {
  
/// @brief JSON builder
class JSONManifestBuilder NEBUILD_MANIFEST_BUILDER {
 public:
  JSONManifestBuilder()           = default;
  ~JSONManifestBuilder() override = default;

 public:
  /// =========================================================== ///
  /// @brief Builds a JSON target from a JSON file.
  /// @param config configuration of build.
  /// @retval true building has succeeded.
  /// @retval false fail to build, see error message.
  /// =========================================================== ///
  bool BuildTarget(BuildConfig& config) override;

  /// =========================================================== ///
  /// @brief Returns the build system name.
  /// =========================================================== ///
  const std::string_view BuildSystem() override;
};

}  // namespace BldKit