// SPDX-License-Identifier: BSD-3-Clause
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-foss-org/build

#pragma once

#include <BldKit/Detail/Config.h>
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