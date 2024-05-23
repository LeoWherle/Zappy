#!/bin/bash
git submodule update --init --recursive
cd gui/raylib/src
make clean
make PLATFORM=PLATFORM_DESKTOP
cd ../../../
cd gui/raylib_cpp
rm -rf build
mkdir build
cd build
cmake ..
make