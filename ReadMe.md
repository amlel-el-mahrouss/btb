# NeBuild

![CI](https://github.com/nekernel-org/nebuild/actions/workflows/c-cpp.yml/badge.svg)
[![License: GPL-3.0](https://img.shields.io/badge/license-BSD--3.0-blue.svg)](LICENSE)

## Requirements:

- GNU C++
- GNU Make

## Guide (GNU Make):

- Run make `build-nebuild-core` and `build-nebuild`.

## Guide (NeBuild):

- Run `nebuild` and pass the path to the manifest file.

## Guide (CMake):

```zsh
# out-of-source configure + build (POSIX)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target nebuild

# or build the provided custom target
cmake --build build --target build-nebuild

# produce a Windows-style executable name on non-Windows hosts:
cmake -S . -B build -DBUILD_WINDOWS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build --target nebuild
```

###### Copyright (C) 2024-2025, Amlal El Mahrouss and NeKernel.org Authors, licensed under the BSD 3 Clause license.
