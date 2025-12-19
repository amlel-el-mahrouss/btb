// ============================================================= //
// NeBuild
// Copyright (C) 2024-2025, Amlal El Mahrouss and NeKernel Authors, licensed under BSD-3 license.
// ============================================================= //

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