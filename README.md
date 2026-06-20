# NE.APP BUILD (nebld)

[![License: GPL-3.0](https://img.shields.io/badge/LICENSE-BSD--3.0-blue.svg)](LICENSE)

Fast and easy to use build system for low-level projects.

## Requirements:

- GNU C++
- GNU Make

## Guide (GNU Make):

- Run make `build-nebld-core` and `build-nebld` to build from the sources.

## Guide (NeBuild):

- Run `nebld` and pass the path to the manifest file to build from the sources:

```sh
nebld targets/osx.json
```

## Guide (CMake):

- Use CMake to build `nebld` from the sources:

```zsh
cmake -S . -B build
cmake --build build
```
###### Copyright (C) 2024-2026, Amlal El Mahrouss and NE.APP, licensed under the BSD 3 Clause license.
