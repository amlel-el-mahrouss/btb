// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, licensed under BSD-3 license.
// ============================================================= //

#pragma once

#include <NeBuildKit/Defines.h>

#define NEBUILD_MANIFEST_BUILDER : public ::NeBuild::IManifestBuilder

namespace NeBuild {
/// =========================================================== ///
/// @brief Builder interface class.
/// @note This class is meant to be used as an interface.
/// =========================================================== ///
class IManifestBuilder {
 public:
  IManifestBuilder()          = default;
  virtual ~IManifestBuilder() = default;

  IManifestBuilder& operator=(const IManifestBuilder&) = default;
  IManifestBuilder(const IManifestBuilder&)            = default;

  /// =========================================================== ///
  /// @brief Builds a TOML target from a file.
  /// @param arg_sz filename size (must be 1 or greater).
  /// @param arg_val filename path (must be a valid language file).
  /// @retval true building has succeeded.
  /// @retval false fail to build, see error message.
  /// =========================================================== ///
  virtual bool BuildTarget(const std::string& arg, const bool dry_run = false) = 0;

  /// =========================================================== ///
  /// @brief Returns the build system name.
  /// =========================================================== ///
  virtual const char* BuildSystem() = 0;
};
}  // namespace NeBuild