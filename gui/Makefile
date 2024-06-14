# Copyright (c) 2020-present Caps Collective & contributors
# Originally authored by Jonathan Moallem (@jonjondev) & Aryeh Zinn (@Raelr)
#
# This code is released under an unmodified zlib license.
# For conditions of distribution and use, please see:
#     https://opensource.org/licenses/Zlib

# Define custom functions
rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
platformpth = $(subst /,$(PATHSEP),$1)

# Set global macros
buildDirName := build
executable := zappy_gui

CFLAGS += -W -Wall -Wextra -Wno-narrowing -Wno-sign-compare
CFLAGS += -Wno-unused-function -Wno-missing-field-initializers

RULE =
# used with make DEBUG=n
ifeq ($(DEBUG), n)
	CFLAGS += -O2
	RULE = "DEBUG=n"
	buildDir := $(buildDirName)/release/
# used with make DEBUG=y
else ifeq ($(DEBUG), y)
	LDFLAGS += -fsanitize=address -fsanitize-address-use-after-scope
	CFLAGS += -g3 -DDEBUG  -fsanitize=address
	RULE = "DEBUG=y"
	buildDir := $(buildDirName)/asan/
else
	CFLAGS += -g
	buildDir := $(buildDirName)/debug/
endif

target := $(buildDir)/$(executable)
sources := $(call rwildcard,src/,*.cpp)
objects := $(patsubst src/%, $(buildDir)/%, $(patsubst %.cpp, %.o, $(sources)))
depends := $(patsubst %.o, %.d, $(objects))
compileFlags := -std=c++17 -I include -I src
linkFlags = -L lib/$(platform) -l raylib -fsanitize=address

# Check for Windows
ifeq ($(OS), Windows_NT)
	# Set Windows macros
	platform := Windows
	CXX ?= g++
	CC ?= gcc
	linkFlags += -Wl,--allow-multiple-definition -pthread -lopengl32 -lgdi32 -lwinmm -mwindows -static -static-libgcc -static-libstdc++
	THEN := &&
	PATHSEP := \$(BLANK)
	MKDIR := -mkdir -p
	RM := -del /q
	COPY = -robocopy "$(call platformpth,$1)" "$(call platformpth,$2)" $3
else
	# Check for MacOS/Linux
	UNAMEOS := $(shell uname)
	ifeq ($(UNAMEOS), Linux)
		# Set Linux macros
		platform := Linux
		CXX ?= g++
		CC ?= gcc
		linkFlags += -l GL -l m -l pthread -l dl -l rt -l X11
	endif
	ifeq ($(UNAMEOS), Darwin)
		# Set macOS macros
		platform := macOS
		CXX ?= clang++
		CC ?= clang
		linkFlags += -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
	endif

	# Set UNIX macros
	THEN := ;
	PATHSEP := /
	MKDIR := mkdir -p
	RM := rm -rf
	COPY = cp $1$(PATHSEP)$3 $2
endif

# Lists phony targets for Makefile
.PHONY: all setup submodules execute clean raygui_setup

# Default target, compiles, executes and cleans
all: $(target)

# Sets up the project for compiling, generates includes and libs
setup: include lib

# Pull and update the the build submodules
submodules:
	git submodule update --init --recursive --depth 1

# Copy the relevant header files into includes
include: submodules
	$(MKDIR) $(call platformpth, ./include)
	$(call COPY,raylib/src,./include,raylib.h)
	$(call COPY,raylib/src,./include,raymath.h)
	$(call COPY,raylib-cpp/include,./include,*.hpp)
	$(call COPY,raygui/src,./include,raygui.h)

RAYGUI_FILE_PATH=raylib/src/raygui.c
raygui_setup:
	cd raylib/src $(THEN) \
	RAYLIB_MODULE_RAYGUI=TRUE "$(MAKE)" PLATFORM=PLATFORM_DESKTOP raygui.c
	echo "#include <stdlib.h>\n\
	#define TextToFloat(text) atof(text)\n\
	$$(cat $(RAYGUI_FILE_PATH))" > $(RAYGUI_FILE_PATH)

# Build the raylib static library file and copy it into lib
lib: submodules raygui_setup
	cd raylib/src $(THEN) \
	RAYLIB_MODULE_RAYGUI=TRUE "$(MAKE)" PLATFORM=PLATFORM_DESKTOP
	$(MKDIR) $(call platformpth, lib/$(platform))
	$(call COPY,raylib/src,lib/$(platform),libraylib.a)

# Link the program and create the executable
$(target): $(objects)
	$(CXX) $(objects) -o $(target) $(linkFlags) $(LDFLAGS)
	cp $(target) .

# Add all rules from dependency files
-include $(depends)

# Compile objects to the build directory
$(buildDir)/%.o: src/%.cpp Makefile
	$(MKDIR) $(call platformpth, $(@D))
	$(CXX) -MMD -MP -c $(compileFlags) $< -o $@ $(CXXFLAGS) $(CFLAGS)

# Clean up all relevant files
clean:

fclean: clean
	$(RM) $(call platformpth, $(buildDir)/*)
