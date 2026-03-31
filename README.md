# The NeBuild System.

[![License: GPL-3.0](https://img.shields.io/badge/LICENSE-BSD--3.0-blue.svg)](LICENSE)

Fast and easy to use build system for low-level projects.

## Requirements:

- GNU C++
- GNU Make

## Guide (GNU Make):

- Run make `build-nebuild-core` and `build-nebuild` to build from source.

## Guide (NeBuild):

- Run `nebuild` and pass the path to the manifest file to build from source:

```sh
nebuild targets/osx.json
```

## Guide (CMake):

- Use CMake to build `nebuild` from source:

```zsh
cmake -S . -B build
cmake --build build
```
###### Copyright (C) 2024-2026, Amlal El Mahrouss and Ne.app Authors, licensed under the BSD 3 Clause license.
