// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, licensed under BSD-3 license.
// ============================================================= //

#pragma once

#include <NeBuildKit/IManifestBuilder.h>
#include <toml++/toml.hpp>

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
  /// @param arg_sz filename size (must be 1 or greater).
  /// @param arg_val filename path (must be a valid TOML file).
  /// @retval true building has succeeded.
  /// @retval false fail to build, see error message.
  /// =========================================================== ///
  bool BuildTarget(const std::string& arg_val, const bool dry_run = false) override;

  /// =========================================================== ///
  /// @brief Returns the build system name.
  /// =========================================================== ///
  const char* BuildSystem() override;
};
}  // namespace NeBuild