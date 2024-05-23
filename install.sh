#!/bin/bash

#Updates the modules if there are any changes
git submodule update --init --recursive

#Builds the raylib library
cd gui/raylib/src
make clean
make PLATFORM=PLATFORM_DESKTOP
cd ../../../

#Builds the raylib_cpp bindings
cd gui/raylib_cpp
rm -rf build
mkdir build
cd build
cmake ..
make