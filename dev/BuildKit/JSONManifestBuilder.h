// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, licensed under BSD-3 license.
// ============================================================= //

#pragma once

#include <BuildKit/IManifestBuilder.h>
#include <json/json.h>

/// @file JSONManifestBuilder.h
/// @brief JSON manifest builder header file.

namespace NeBuild {
/// @brief JSON builder
class JSONManifestBuilder final NEBUILD_MANIFEST_BUILDER {
 public:
  JSONManifestBuilder()           = default;
  ~JSONManifestBuilder() override = default;

  JSONManifestBuilder& operator=(const JSONManifestBuilder&) = default;
  JSONManifestBuilder(const JSONManifestBuilder&)            = default;

 public:
  /// =========================================================== ///
  /// @brief Builds a JSON target from a JSON file.
  /// @param arg_sz filename size (must be 1 or greater).
  /// @param arg_val filename path (must be a valid JSON file).
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