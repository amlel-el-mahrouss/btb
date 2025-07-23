// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, all rights reserved.
// ============================================================= //

#pragma once

#include <BuildKit/Includes.h>
#include <BuildKit/Macros.h>

#define NEBUILD_MANIFEST_BUILDER : public BTB::IManifestBuilder

namespace BTB {
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
  virtual bool buildTarget(int arg_sz, const char* arg_val, const bool dry_run = false) = 0;
  virtual const char* buildSystem() = 0;
};
}  // namespace BTB