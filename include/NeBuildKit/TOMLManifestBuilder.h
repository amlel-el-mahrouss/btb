// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, licensed under BSD-3 license.
// ============================================================= //

#pragma once

#include <NeBuildKit/IManifestBuilder.h>

/// @file TOMLManifestBuilder.h
/// @brief TOML manifest builder header file.

namespace NeBuild {
/// @brief TOML builder
class TOMLManifestBuilder final NEBUILD_MANIFEST_BUILDER {
 public:
  TOMLManifestBuilder()           = default;
  ~TOMLManifestBuilder() override = default;

  TOMLManifestBuilder& operator=(const TOMLManifestBuilder&) = default;
  TOMLManifestBuilder(const TOMLManifestBuilder&)            = default;

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
  const char* BuildSystem() override;
};
}  // namespace NeBuild