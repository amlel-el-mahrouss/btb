// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, licensed under BSD-3 license.
// ============================================================= //

#pragma once

#include <BuildKit/IManifestBuilder.h>
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
  /// @brief Builds a TOML target.
  /// @param arg_sz filename size
  /// @param arg_val filename path.
  /// @retval true build succeeded.
  /// @retval false failed to build.
  bool        BuildTarget(const std::string& arg_val, const bool dry_run = false) override;
  const char* BuildSystem() override;
};
}  // namespace NeBuild