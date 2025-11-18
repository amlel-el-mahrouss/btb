cmake_minimum_required(VERSION 3.16)

project(nebuild VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/dev ${CMAKE_SOURCE_DIR}/vendor)

file(GLOB NEBUILD_CLI_SOURCES "${CMAKE_SOURCE_DIR}/dev/cli/*.cc")
file(GLOB NEBUILD_SRC_SOURCES "${CMAKE_SOURCE_DIR}/dev/src/*.cc")
set(NEBUILD_SOURCES ${NEBUILD_CLI_SOURCES} ${NEBUILD_SRC_SOURCES})

add_executable(nebuild ${NEBUILD_SOURCES})

target_include_directories(nebuild PRIVATE ${CMAKE_SOURCE_DIR}/dev ${CMAKE_SOURCE_DIR}/vendor)

option(BUILD_WINDOWS "Produce a Windows executable name (nebuild.exe)" OFF)
if(BUILD_WINDOWS)
  set_target_properties(nebuild PROPERTIES OUTPUT_NAME "nebuild.exe")
endif()

add_custom_target(build-nebuild
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target nebuild
  COMMENT "=> NeBuild built successfully for POSIX."
)

add_custom_target(build-nebuild-windows
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target nebuild
  COMMENT "=> NeBuild built successfully for Windows (configure with -DBUILD_WINDOWS=ON)."
)

message(STATUS "Project: nebuild")
message(STATUS "Sources: ${NEBUILD_SOURCES}")
message(STATUS "Include dirs: ${CMAKE_SOURCE_DIR}/dev;${CMAKE_SOURCE_DIR}/vendor")
message(STATUS "To build for Windows-style executable: configure with -DBUILD_WINDOWS=ON")
