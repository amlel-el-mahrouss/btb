# // ============================================================= //
# // NeBuild
# // Copyright (C) 2024-2026, Amlal El Mahrouss and NeKernel Authors, licensed under BSD-3 license.
# // ============================================================= //

.PHONY: all
all: nebld.exe
	@echo "=> Successfully built NeBuild for Windows."

CL=cl.exe

nebld.exe: src/*.cpp
	@$(CL) /onebld.exe /DNEBUILD_INTERNAL_SDK /DNEBUILD_WINDOWS /std:c++20 /EHsc /I"include" /I"vendor" $(**:.cpp=.cpp)
