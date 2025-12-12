// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, licensed under BSD-3 license.
// ============================================================= //

#pragma once

#include <NeBuildKit/IManifestBuilder.h>

/// @file JSONManifestBuilder.h
/// @brief JSON manifest builder header file.

namespace NeBuild {
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
}  // namespace NeBuild