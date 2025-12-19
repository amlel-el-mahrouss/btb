# // ============================================================= //
# // NeBuild
# // Copyright (C) 2025, Amlal El Mahrouss, licensed under BSD-3 license.
# // ============================================================= //

# AMLALE: Update the CMake version, which requires a version that was too old.
cmake_minimum_required(VERSION 3.30)

# Append .exe when it's a Windows build (The Windows loader requires it)
if(BUILD_WINDOWS)
  set_target_properties(nebuild PROPERTIES OUTPUT_NAME "nebuild.exe")

    add_custom_target(build-nebuild-windows
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target nebuild
    COMMENT "=> NeBuild built successfully for Windows (configure with -DBUILD_WINDOWS=ON)."
    )
endif()

message(STATUS "To build for Windows-style executable: configure with -DBUILD_WINDOWS=ON")