#!/bin/bash
git submodule update --init --recursive
cd gui/raylib/src
make clean
make PLATFORM=PLATFORM_DESKTOP