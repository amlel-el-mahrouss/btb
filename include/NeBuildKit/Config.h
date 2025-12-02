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

#define LIBNEBUILD_VERSION "v0.0.7-buildkit"

#define LIBNEBUILD_VERSION_BCD 0x0007

#define LIBNEBUILD_VERSION_MAJOR 0
#define LIBNEBUILD_VERSION_MINOR 0
#define LIBNEBUILD_VERSION_PATCH 7

#define LIBNEBUILD_EXPORT_C extern "C"

#define LIBNEBUILD_UNUSED(X) ((void) X)

namespace NeBuild {
  struct BuildConfig final {
    bool has_failed_{false};
    bool dry_run_{false};
    std::string path_{};

    explicit operator bool() {
      return has_failed_;
    }

    BuildConfig() = default;
    ~BuildConfig() {}
  };
}

namespace NeBuild::Logger {
/// @brief replacement for std::cout for NeBuild logging.
inline std::ostream& info() noexcept {
  auto& out = std::cout;
  out << rang::fg::red << "nebuild: " << rang::style::reset;
  return out;
}
}  // namespace NeBuild::Logger


