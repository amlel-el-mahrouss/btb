SUDO=sudo
GCC=g++
GCC_MINGW=x86_64-w64-mingw32-g++
CXXFLAGS=-I./ -I./vendor
CXXSTD= -std=c++20
SRC=$(wildcard cli/*.cc) $(wildcard src/*.cc)
OUT=nebuild
CP=cp

.PHONY: build-nebuild
build-nebuild:
	$(SUDO) $(GCC) $(CXXFLAGS) $(SRC) $(CXXSTD) -o $(OUT)
	$(SUDO) $(CP) $(OUT) /usr/local/bin

.PHONY: build-nebuild-windows
build-nebuild-windows:
	$(GCC_MINGW) $(CXXFLAGS) $(SRC) -o $(OUT).exe

.PHONY: help
help:
	@echo "=> help: Show this help message."
	@echo "=> build-nebuild-windows: Build BTB for Windows."
	@echo "=> build-nebuild: Build BTB for POSIX."
