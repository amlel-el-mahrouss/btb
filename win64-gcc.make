# // ============================================================= //
# // NeBuild
# // Copyright (C) 2024-2026, Amlal El Mahrouss and NeKernel Authors, licensed under BSD-3 license.
# // ============================================================= //

.PHONY: nebuild.exe
nebuild.exe: CLI.o JSONManifestBuilder.o IManifestBuilder.o TOMLManifestBuilder.o 
	ld $(wildcard src/*.o) -lc -o $@

%.o: src/%.cpp
	g++ -c -o $@ -D=NEBUILD_INTERNAL_SDK -D=NEBUILD_WINDOWS -std=c++20 -Iinclude -Ivendor $<
