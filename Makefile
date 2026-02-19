# // ============================================================= //
# // NeBuild
# // Copyright (C) 2024-2026, Amlal El Mahrouss and NeKernel Authors, licensed under BSD-3 license.
# // ============================================================= //

SUDO=sudo
GCC=clang++
GCC_MINGW=x86_64-w64-mingw32-g++
CXXFLAGS=-I./include -L/usr/local/lib -I./vendor -lNeBuildKit
CXXSTD= -std=c++20
SRC=$(wildcard src/cli/*.cpp)
OUT=nebuild
CP=cp

.PHONY: build-nebuild
build-nebuild:
	$(SUDO) $(GCC) $(CXXFLAGS) $(SRC) $(CXXSTD) -o $(OUT)
	@echo "=> NeBuild built successfully for POSIX."

.PHONY: build-nebuild-windows
build-nebuild-windows:
	$(GCC_MINGW) $(CXXFLAGS) $(SRC) -o $(OUT).exe
	@echo "=> NeBuild built successfully for Windows."

.PHONY: help
help:
	@echo "=> NEBUILD HELP:"
	@echo "=> help: Show this help message."
	@echo "=> build-nebuild-windows: Build NeBuild for Windows."
	@echo "=> build-nebuild: Build NeBuild for POSIX."
