# // ============================================================= //
# // NeBuild System.
# // Copyright (C) 2025-2026, Amlal El Mahrouss and Ne.app Author, licensed under BSD-3 license.
# // ============================================================= //

# AMLALE: Update the CMake version, which requires a version that was too old.
cmake_minimum_required(VERSION 3.30)

# Append .exe when it's a Windows build (The Windows loader requires it)
if(DEFINED BUILD_WINDOWS)
  set_target_properties(nebld PROPERTIES OUTPUT_NAME "nebld.exe")

    add_custom_target(build-nebld-windows
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target nebld
    COMMENT "=> NeBuild successfully built for Windows (configure with -DBUILD_WINDOWS=ON)."
    )
endif()

message(STATUS "To build for Windows-style executable: configure with -DBUILD_WINDOWS=ON")
