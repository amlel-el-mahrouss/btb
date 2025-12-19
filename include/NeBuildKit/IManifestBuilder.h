// ============================================================= //
// NeBuild
// Copyright (C) 2024-2025, Amlal El Mahrouss and NeKernel Authors, licensed under BSD-3 license.
// ============================================================= //

#pragma once

#include <NeBuildKit/Detail/Config.h>
#include <string_view>

#define NEBUILD_MANIFEST_BUILDER \
  final:                         \
  public                         \
  ::NeBuild::IManifestBuilder

namespace NeBuild {
/// =========================================================== ///
/// @brief Builder interface class.
/// @note This class is meant to be used as an interface.
/// =========================================================== ///
class IManifestBuilder {
 public:
  IManifestBuilder()          = default;
  virtual ~IManifestBuilder() = default;

  IManifestBuilder& operator=(const IManifestBuilder&) = delete;
  IManifestBuilder(const IManifestBuilder&)            = delete;

  /// =========================================================== ///
  /// @brief Builds a TOML target from a file.
  /// @param config configuration of build.
  /// @retval true building has succeeded.
  /// @retval false fail to build, see error message.
  /// =========================================================== ///
  virtual bool BuildTarget(BuildConfig& config) { return false; }

  /// =========================================================== ///
  /// @brief Returns the build system name.
  /// =========================================================== ///
  virtual const std::string_view BuildSystem() { return "(null)"; }
};
}  // namespace NeBuild