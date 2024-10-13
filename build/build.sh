#!/bin/bash

# Set project root, source, include, and texture paths
PROJECT_ROOT="/Users/matt/Documents/projects/development/learning_c/rpg_game"
SRC_DIR="$PROJECT_ROOT/src"
INCLUDE_DIR="$PROJECT_ROOT/include"
BUILD_DIR="$PROJECT_ROOT/build"
TEXTURE_PATH="$PROJECT_ROOT/textures"

# SDL2 and SDL2_image include and library paths
SDL2_INCLUDE="/opt/homebrew/include/SDL2"
SDL2_LIB="/opt/homebrew/lib"

# Ensure the textures directory exists
if [ ! -d "$TEXTURE_PATH" ]; then
    echo "Error: Textures directory not found in $TEXTURE_PATH"
    exit 1
fi

# Ensure the build directory exists
mkdir -p "$BUILD_DIR"

# Compile the project
echo "Compiling the project..."
gcc -o "$BUILD_DIR/main" $(find "$SRC_DIR" -name '*.c') \
    -I"$INCLUDE_DIR" -I"$SDL2_INCLUDE" \
    -L"$SDL2_LIB" -lSDL2 -lSDL2_image

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Executable is located at $BUILD_DIR/main"
    echo "Make sure textures are in: $TEXTURE_PATH"
else
    echo "Compilation failed."
fi