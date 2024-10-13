#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "textures.h"
#include <stdlib.h>
#include <string.h>

// Helper function to load individual textures with dynamic path setting
SDL_Texture* load_single_texture(SDL_Renderer* renderer, const char* filename) {
    // Retrieve the base path of the executable
    char* base_path = SDL_GetBasePath();
    if (base_path == NULL) {
        fprintf(stderr, "Failed to get base path: %s\n", SDL_GetError());
        return NULL;
    }

    // Define the relative texture folder path
    const char* relative_path = "textures/";
    size_t full_path_length = strlen(base_path) + strlen(relative_path) + strlen(filename) + 1;

    // Allocate memory for the full texture path
    char* full_path = (char*)malloc(full_path_length);
    if (full_path) {
        snprintf(full_path, full_path_length, "%s%s%s", base_path, relative_path, filename);
    } else {
        fprintf(stderr, "Failed to allocate memory for texture path.\n");
        SDL_free(base_path);
        return NULL;
    }

    // Load the texture image file
    SDL_Surface* surface = IMG_Load(full_path);
    free(full_path);  // Free the path string as it's no longer needed
    SDL_free(base_path);

    if (!surface) {
        fprintf(stderr, "Failed to load texture %s: %s\n", filename, IMG_GetError());
        return NULL;
    }

    // Convert surface to an SDL_Texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);  // Free surface after converting to texture

    if (!texture) {
        fprintf(stderr, "Failed to create texture from %s: %s\n", filename, SDL_GetError());
    }
    return texture;
}

// Function to load all textures and return a Textures struct
Textures* load_textures(SDL_Renderer* renderer) {
    Textures* textures = malloc(sizeof(Textures));
    if (!textures) {
        fprintf(stderr, "Failed to allocate memory for textures.\n");
        return NULL;
    }

    // Load each texture individually
    textures->player = load_single_texture(renderer, "player.png");
    textures->npc = load_single_texture(renderer, "npc.png");
    textures->grass = load_single_texture(renderer, "grass.png");
    textures->water = load_single_texture(renderer, "water.png");
    textures->mountain = load_single_texture(renderer, "mountain.png");

    // Verify all textures loaded successfully
    if (!textures->player || !textures->npc || !textures->grass || !textures->water || !textures->mountain) {
        fprintf(stderr, "Failed to load one or more textures.\n");
        // Free any textures that were successfully loaded
        if (textures->player) SDL_DestroyTexture(textures->player);
        if (textures->npc) SDL_DestroyTexture(textures->npc);
        if (textures->grass) SDL_DestroyTexture(textures->grass);
        if (textures->water) SDL_DestroyTexture(textures->water);
        if (textures->mountain) SDL_DestroyTexture(textures->mountain);
        free(textures);
        return NULL;
    }

    return textures;
}

// Function to clean up textures
void cleanup_textures(Textures* textures) {
    if (textures) {
        if (textures->player) SDL_DestroyTexture(textures->player);
        if (textures->npc) SDL_DestroyTexture(textures->npc);
        if (textures->grass) SDL_DestroyTexture(textures->grass);
        if (textures->water) SDL_DestroyTexture(textures->water);
        if (textures->mountain) SDL_DestroyTexture(textures->mountain);
        free(textures);
    }
}
