# // ============================================================= //
# // NeBuild
# // Copyright (C) 2024-2026, Amlal El Mahrouss and NeKernel Authors, licensed under BSD-3 license.
# // ============================================================= //

.PHONY: all
all: nebuild.exe
	@echo "=> Successfully built NeBuild for Windows."

CL=cl.exe

nebuild.exe: src/CommandLine/CLI.cpp src/NeBuildKit/*.cpp
	@$(CL) /onebuild.exe /DNEBUILD_INTERNAL_SDK /DNEBUILD_WINDOWS /std:c++20 /EHsc /I"include" /I"vendor" $(**:.cpp=.cpp)
