#include <SDL.h> 
#include <SDL.h>
#include <SDL_image.h>  
#include <stdlib.h>
#include "utils.h"
#include "textures.h"

void control_fps(Uint32 frame_time) {
    const int TARGET_FPS = 60;
    const int FRAME_DELAY = 1000 / TARGET_FPS;

    if (FRAME_DELAY > frame_time) SDL_Delay(FRAME_DELAY - frame_time);
}

void cleanup(Textures* textures, SDL_Renderer* renderer, SDL_Window* window, char** map, int map_height) {
    if (textures) {
        SDL_DestroyTexture(textures->player);
        SDL_DestroyTexture(textures->npc);
        SDL_DestroyTexture(textures->grass);
        SDL_DestroyTexture(textures->water);
        SDL_DestroyTexture(textures->mountain);
        free(textures);
    }

    for (int i = 0; i < map_height; i++) {
        free(map[i]);
    }
    free(map);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();  // Quit SDL_image subsystem
    SDL_Quit();  // Quit SDL subsystem
}

