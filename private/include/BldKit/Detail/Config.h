// SPDX-License-Identifier: BSD-3-Clause
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (see LICENSE file)
// Official repository: https://github.com/ne-app-eu/bld

#pragma once

/// =========================================================== ///
/// @author Amlal El Mahrouss
/// =========================================================== ///

#include <rang/rang.h>
#include <cassert>
#include <iostream>

#define NEBUILD_VERSION "v1.0.0-buildkit"

#define NEBUILD_VERSION_BCD 0x1000

#define NEBUILD_VERSION_MAJOR 0
#define NEBUILD_VERSION_MINOR 0
#define NEBUILD_VERSION_PATCH 9

#define NEBUILD_EXPORT_C extern "C"

#define NEBUILD_UNUSED(X) ((void) X)

#define b_internal private

#ifdef NEBUILD_INTERNAL_SDK
#undef b_internal
#define b_internal public
#endif

namespace BldKit {
  
struct BuildConfig final {
  b_internal : bool has_failed_{false};
  bool              dry_run_{false};
  std::string       path_{};

 public:
  explicit operator bool() { return has_failed_; }

  bool dry_run() { return dry_run_; }
  void dry_run(const bool& dr) { dry_run_ = dr; }

  bool has_failed() { return has_failed_; }
  void has_failed(const bool& dr) { has_failed_ = dr; }

  const std::string& path() { return path_; }
  void               path(const std::string& path) { path_ = path; }

  BuildConfig()  = default;
  ~BuildConfig() = default;

  BuildConfig& operator=(const BuildConfig&) = default;
  BuildConfig(const BuildConfig&)            = default;

};

}  // namespace BldKit

/// \brief Logger namespace.
namespace BldKit::Logger {

/// @brief replacement for std::cout for NeBuild logging.
/// @todo change this to spdlog?
inline std::ostream& info() noexcept {
  auto& out = std::cout;
  out << rang::fg::red << "nebld: " << rang::style::reset;
  return out;
}

}  // namespace BldKit::Logger
