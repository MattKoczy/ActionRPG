# Compiler and flags
CC = gcc
CFLAGS = -g -DSDL_MAIN_HANDLED -I$(SDL2_INCLUDE) -Iinclude  # SDL setup flags

# Directories
SRC_DIR = src
OBJ_DIR = build/obj
INCLUDE_DIR = include

# Detect platform and set SDL paths
ifeq ($(OS),Windows_NT)
    SDL2_INCLUDE = C:/msys64/mingw64/include/SDL2   # SDL2 include directory for Windows
    SDL2_LIB = C:/msys64/mingw64/lib                # SDL2 library directory for Windows
    LDFLAGS = -L$(SDL2_LIB) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
    EXECUTABLE = game.exe  # Set .exe extension for Windows
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        SDL2_INCLUDE = /opt/homebrew/include/SDL2       # SDL2 include directory for macOS
        SDL2_LIB = /opt/homebrew/lib                    # SDL2 library directory for macOS
        LDFLAGS = -L$(SDL2_LIB) -lSDL2 -lSDL2_image -framework Cocoa  # Add Cocoa framework for macOS
        EXECUTABLE = game_macos                         # Name executable as game_macos on macOS
    else
        SDL2_INCLUDE = /usr/include/SDL2                # SDL2 include directory for Ubuntu
        SDL2_LIB = /usr/lib/x86_64-linux-gnu            # SDL2 library directory for Ubuntu
        LDFLAGS = -L$(SDL2_LIB) -lSDL2 -lSDL2_image
        EXECUTABLE = game_linux                         # Name executable as game_linux on Ubuntu
    endif
endif

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)            # Include all .c files in src/
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target to build the executable
all: $(EXECUTABLE)

# Link object files to create the executable in the root directory
$(EXECUTABLE): $(OBJS)
	@echo "Linking executable..."
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compile each .c file to .o in the build/obj directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if they don’t exist
$(OBJ_DIR):
	mkdir -p $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)

# Phony targets
.PHONY: all clean