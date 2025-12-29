# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

NeBuild is a minimal build system that uses manifest files (JSON or TOML) to define build configurations. It's a C++20 project that compiles C++ projects based on declarative manifest files, supporting both POSIX and Windows platforms.

## Build Commands

### Using Make (Primary)
```bash
# Build NeBuild for POSIX systems (uses clang++)
make build-nebuild

# Build NeBuild for Windows (cross-compile with MinGW)
make build-nebuild-windows

# Show available make targets
make help
```

### Using CMake (Alternative)
```bash
# Configure and build
cmake -S . -B build
cmake --build build

# Or use the custom target
cmake --build build --target build-nebuild
```

### Using NeBuild (Self-hosting)
```bash
# Build a project using a manifest file
./nebuild path/to/manifest.json
./nebuild path/to/manifest.toml

# Dry-run mode (don't execute build)
./nebuild -dry-run manifest.json
./nebuild -n manifest.json

# Check build system name
./nebuild manifest.json -build-system

# Show version
./nebuild -v
```

## Architecture

### Core Components

**Manifest Builders** (`src/lib/`, `include/NeBuildKit/`)
- `IManifestBuilder`: Abstract base class defining the builder interface
- `JSONManifestBuilder`: Parses `.json` manifest files using nlohmann/json
- `TOMLManifestBuilder`: Parses `.toml` manifest files using toml++
- Each builder implements `BuildTarget(BuildConfig&)` and `BuildSystem()`

**CLI** (`src/cli/main.cc`)
- Entry point that routes manifest files to appropriate builder based on file extension
- Supports multi-threaded builds (each manifest file processed in a thread)
- Handles command-line flags: `-v`, `-dry-run`, `-n`, `-h`, `-build-system`

**Configuration** (`include/NeBuildKit/Detail/Config.h`)
- `BuildConfig`: Holds build state (path, failure status, dry-run mode)
- `Logger::info()`: Custom logging with colored output via rang library
- Version constants: `NEBUILD_VERSION`, `NEBUILD_VERSION_BCD`

### Manifest File Format

Both JSON and TOML manifests support the same fields:
- `compiler_path`: Path to compiler executable (e.g., "clang++")
- `compiler_std`: C++ standard (e.g., "c++20")
- `compiler_headers_path`: Additional header search paths (optional)
- `headers_path`: Header include directories
- `sources_path`: Source files to compile
- `output_name`: Output executable/library path
- `compiler_flags`: Additional compiler flags
- `cpp_macros`: Preprocessor macros to define
- `run_after_build`: Whether to run the output after building

See `example/` directory for reference manifests.

### Dependencies (vendor/)

- **nlohmann/json**: JSON parsing library
- **toml++**: TOML parsing library
- **rang**: Terminal color output library

All dependencies are vendored and included via `-I./vendor` flag.

## Code Structure

```
src/
├── cli/          # Command-line interface
│   └── main.cc   # Main entry point
└── lib/          # Core build logic
    ├── IManifestBuilder.cc
    ├── JSONManifestBuilder.cc
    └── TOMLManifestBuilder.cc

include/NeBuildKit/
├── Detail/
│   └── Config.h              # BuildConfig, Logger, version info
├── IManifestBuilder.h        # Base interface
├── JSONManifestBuilder.h     # JSON builder
└── TOMLManifestBuilder.h     # TOML builder
```

## Development Notes

### Compiler Requirements
- Requires C++20 support
- Default compiler: `clang++` (can be overridden in Makefile)
- CMake minimum version: 3.30

### File Extension Routing
The CLI automatically selects the builder based on file extension:
- `.json` → `JSONManifestBuilder`
- `.toml` → `TOMLManifestBuilder`
- Other extensions → Error

### Build Process Flow
1. CLI parses command-line arguments
2. For each manifest file, spawn a thread
3. Create appropriate builder based on file extension
4. Builder parses manifest and constructs compiler command
5. Execute compiler via `std::system()`
6. Optionally run output if `run_after_build` is true
7. Join thread and check `BuildConfig` for failures

### Working with Builders

When modifying or adding builders:
- Inherit from `IManifestBuilder` using the `NEBUILD_MANIFEST_BUILDER` macro
- Implement `BuildTarget(BuildConfig&)` to parse manifest and execute build
- Implement `BuildSystem()` to return a descriptive name
- Use `NeBuild::Logger::info()` for all output (not `std::cout`)
- Set `config.has_failed_` on errors
- Check `config.dry_run_` before executing system commands

### Branches
- `develop`: Main development branch (default, CI enabled)
- Other feature branches for specific work

## CI/CD

GitHub Actions runs on the `develop` branch:
- Runs on Ubuntu with `build-essential`
- Builds using `make build-nebuild`
