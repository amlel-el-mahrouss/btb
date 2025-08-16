// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, all rights reserved.
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
  /// @brief Builds a JSON target.
  /// @param arg_sz filename size
  /// @param arg_val filename path.
  /// @retval true build succeeded.
  /// @retval false failed to build.
  bool        BuildTarget(const std::string& arg_val, const bool dry_run = false) override;
  const char* BuildSystem() override;
};
}  // namespace NeBuild