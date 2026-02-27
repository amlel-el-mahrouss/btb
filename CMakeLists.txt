# // ============================================================= //
# // NeBuild System.
# // Copyright (C) 2025-2026, Amlal El Mahrouss and Ne.org, licensed under BSD-3 license.
# // ============================================================= //

# AMLALE: Update the CMake version, which requires a version that was too old.
cmake_minimum_required(VERSION 3.30)

project(nebuild VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/vendor)

file(GLOB NEBUILD_CLI_SOURCES "${CMAKE_SOURCE_DIR}/src/CommandLine/*.cc")
file(GLOB NEBUILD_SRC_SOURCES "${CMAKE_SOURCE_DIR}/src/NeBuildKit/*.cc")
set(NEBUILD_SOURCES ${NEBUILD_CLI_SOURCES} ${NEBUILD_SRC_SOURCES})

add_executable(nebuild ${NEBUILD_SOURCES})

target_include_directories(nebuild PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/vendor)

option(BUILD_WINDOWS "=> Produce a Windows executable name (nebuild.exe)" OFF)

add_custom_target(build-nebuild
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target nebuild
  COMMENT "=> NeBuild built successfully for POSIX."
)

message(STATUS "=> Sources: ${NEBUILD_SOURCES}")
message(STATUS "=> Include Dirs: ${CMAKE_SOURCE_DIR}/src;${CMAKE_SOURCE_DIR}/vendor")

include(install_windows.cmake)
