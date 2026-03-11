// SPDX-License-Identifier: BSD-3-Clause
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-foss-org/build

#pragma once

#include <NeBuildKit/IManifestBuilder.h>

/// @file TOMLManifestBuilder.h
/// @brief TOML manifest builder header file.

namespace NeBuild {
/// @brief TOML builder
class TOMLManifestBuilder NEBUILD_MANIFEST_BUILDER {
 public:
  TOMLManifestBuilder()           = default;
  ~TOMLManifestBuilder() override = default;

 public:
  /// =========================================================== ///
  /// @brief Builds a TOML target from a TOML file.
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
}  // namespace NeBuild