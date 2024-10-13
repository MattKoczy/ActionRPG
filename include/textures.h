#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL.h>

#define TILE_SIZE 32

typedef struct {
    SDL_Texture* player;
    SDL_Texture* npc;
    SDL_Texture* grass;
    SDL_Texture* water;
    SDL_Texture* mountain;
} Textures;

// Function prototypes for texture management
Textures* load_textures(SDL_Renderer* renderer);
void render_map(SDL_Renderer* renderer, Textures* textures, char** map, int map_width, int map_height);
void cleanup(Textures* textures, SDL_Renderer* renderer, SDL_Window* window, char** map, int map_height);


#endif // TEXTURES_H
