# // ============================================================= //
# // NeBuild
# // Copyright (C) 2024-2026, Amlal El Mahrouss and NeKernel Authors, licensed under BSD-3 license.
# // ============================================================= //

.PHONY: nebld.exe
nebld.exe: 
	g++ -std=c++20 -o $@ -DNEBUILD_INTERNAL_SDK -DNEBUILD_WINDOWS -std=gnu++23 -Iinclude -Ivendor $(wildcard src/*.cpp)
