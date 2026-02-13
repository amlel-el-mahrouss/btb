// ============================================================= //
// NeBuild
// Copyright (C) 2024-2025, Amlal El Mahrouss and NeKernel Authors, licensed under BSD-3 license.
// ============================================================= //

#pragma once

/// =========================================================== ///
/// @author Amlal El Mahrouss
/// =========================================================== ///

#include <rang/rang.h>
#include <cassert>
#include <iostream>

#define NEBUILD_VERSION "v0.0.8-buildkit"

#define NEBUILD_VERSION_BCD 0x0007

#define NEBUILD_VERSION_MAJOR 0
#define NEBUILD_VERSION_MINOR 0
#define NEBUILD_VERSION_PATCH 7

#define NEBUILD_EXPORT_C extern "C"

#define NEBUILD_UNUSED(X) ((void) X)

#define b_internal private

#ifdef NEBUILD_INTERNAL_SDK
#undef b_internal
#define b_internal public
#endif

namespace NeBuild {
struct BuildConfig final {
  b_internal : bool has_failed_{false};
  bool              dry_run_{false};
  std::string       path_{};

 public:
  explicit operator bool() { return has_failed_; }

  bool dry_run() { return dry_run_; }
  void dry_run(const bool dr) { dry_run_ = dr; }

  bool has_failed() { return has_failed_; }
  void has_failed(const bool dr) { has_failed_ = dr; }

  const std::string& path() { return path_; }
  void               path(const std::string& pat) { path_ = pat; }

  BuildConfig()  = default;
  ~BuildConfig() = default;
};
}  // namespace NeBuild

/// \brief Logger namespace.
namespace NeBuild::Logger {
/// @brief replacement for std::cout for NeBuild logging.
/// @todo change this to spdlog?
inline std::ostream& info() noexcept {
  auto& out = std::cout;
  out << rang::fg::red << "nebuild: " << rang::style::reset;
  return out;
}
}  // namespace NeBuild::Logger
