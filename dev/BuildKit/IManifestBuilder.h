// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, all rights reserved.
// ============================================================= //

#pragma once

#include <BuildKit/Defines.h>

#define NEBUILD_MANIFEST_BUILDER : public NeBuild::IManifestBuilder

namespace NeBuild {
/// @brief Builder interface class.
/// @note This class is meant to be used as an interface.
class IManifestBuilder {
 public:
  IManifestBuilder() = default;
  virtual ~IManifestBuilder() = default;

  IManifestBuilder& operator=(const IManifestBuilder&) = default;
  IManifestBuilder(const IManifestBuilder&)            = default;

  /// @brief Builds a target using the implemented laguage.
  /// @param arg_sz filename size
  /// @param arg_val filename path.
  /// @retval true succeeded.
  /// @retval false failed.
  virtual bool BuildTarget(const std::string& arg, const bool dry_run = false) = 0;
  virtual const char* BuildSystem() = 0;
};
}  // namespace NeBuild