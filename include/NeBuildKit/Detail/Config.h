// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, licensed under BSD-3 license.
// ============================================================= //

#pragma once

/// =========================================================== ///
/// @author Amlal El Mahrouss
/// =========================================================== ///

#include <rang/rang.h>
#include <cassert>
#include <iostream>

#define LIKELY(ARG) ((ARG) ? assert(false) : ((void) 0))
#define UNLIKELY(ARG) LIKELY(!(ARG))

#define NEBUILD_VERSION "v0.0.8-buildkit"

#define NEBUILD_VERSION_BCD 0x0007

#define NEBUILD_VERSION_MAJOR 0
#define NEBUILD_VERSION_MINOR 0
#define NEBUILD_VERSION_PATCH 7

#define NEBUILD_EXPORT_C extern "C"

#define NEBUILD_UNUSED(X) ((void) X)

namespace NeBuild {
struct BuildConfig final {
  bool        has_failed_{false};
  bool        dry_run_{false};
  std::string path_{};

  explicit operator bool() { return has_failed_; }

  BuildConfig() = default;
  ~BuildConfig() = default;
};
}  // namespace NeBuild

namespace NeBuild::Logger {
/// @brief replacement for std::cout for NeBuild logging.
inline std::ostream& info() noexcept {
  auto& out = std::cout;
  out << rang::fg::red << "nebuild: " << rang::style::reset;
  return out;
}
}  // namespace NeBuild::Logger
