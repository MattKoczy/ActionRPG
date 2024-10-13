#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include "textures.h"
#include "map.h"
#include "movement.h"
#include "utils.h"

int main(int argc, char* args[]) {
    srand(time(NULL));

    // Initialize SDL and SDL_image
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL/SDL_image could not initialize! Error: %s\n", SDL_GetError());
        return -1;
    }

    // Set render quality hint for better texture scaling
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    // Disable mouse cursor
    SDL_ShowCursor(SDL_DISABLE);

    // Set up map dimensions and player position
    int map_width, map_height, player_x, player_y;
    char** map = init_map(&map_width, &map_height, &player_x, &player_y);

    // Create window and software renderer
    SDL_Window* window = SDL_CreateWindow("RPG Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          map_width * TILE_SIZE, map_height * TILE_SIZE, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    // Explicitly set display mode for consistent rendering
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    SDL_SetWindowDisplayMode(window, &displayMode);

    // Load textures
    Textures* textures = load_textures(renderer);
    if (!textures) {
        printf("Failed to load one or more textures.\n");
        return -1;
    }

    // Main game loop
    int quit = 0;
    SDL_Event event;
    while (!quit) {
        Uint32 frame_start = SDL_GetTicks();

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w: move_player(map, map_width, map_height, &player_x, &player_y, 0, -1); break;
                    case SDLK_s: move_player(map, map_width, map_height, &player_x, &player_y, 0, 1); break;
                    case SDLK_a: move_player(map, map_width, map_height, &player_x, &player_y, -1, 0); break;
                    case SDLK_d: move_player(map, map_width, map_height, &player_x, &player_y, 1, 0); break;
                }
            }
        }

        SDL_RenderClear(renderer);
        render_map(renderer, textures, map, map_width, map_height);
        SDL_RenderPresent(renderer);

        Uint32 frame_time = SDL_GetTicks() - frame_start;
        control_fps(frame_time);
    }

    cleanup(textures, renderer, window, map, map_height);

    return 0;
}
