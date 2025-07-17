// ============================================================= //
// nebuild
// Copyright (C) 2024-2025, Amlal El Mahrouss, all rights reserved.
// ============================================================= //

#pragma once

extern "C" {
#include <assert.h>
}

#include <rang.h>

#define LIKELY(ARG) ((ARG) ? assert(false) : ((void) 0))
#define UNLIKELY(ARG) LIKELY(!(ARG))

#define LIBBTB_VERSION "v0.0.1-libBTB"

#define LIBBTB_VERSION_BCD 0x0001

#define LIBBTB_VERSION_MAJOR 1
#define LIBBTB_VERSION_MINOR 1
#define LIBBTB_VERSION_PATCH 0

#define LIBBTB_UNUSED(X) ((void) X)

namespace BTB::Logger {
/// @brief replacement for std::cout for BTB logging.
inline std::ostream& info() noexcept {
  auto& out = std::cout;
  out << rang::fg::red << "nebuild: " << rang::style::reset;
  return out;
}
}  // namespace BTB::Logger
