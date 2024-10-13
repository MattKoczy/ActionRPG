#include <SDL.h>
#include "map.h"      // For map constants like WATER, PLAYER, etc.
#include "textures.h"

// Corrected function signature to match textures.h
void render_map(SDL_Renderer* renderer, Textures* textures, char** map, int map_width, int map_height) {
    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            SDL_Rect dest_rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            
            switch (map[y][x]) {
                case PLAYER:
                    SDL_RenderCopy(renderer, textures->player, NULL, &dest_rect);
                    break;
                case NPC:
                    SDL_RenderCopy(renderer, textures->npc, NULL, &dest_rect);
                    break;
                case OBSTACLE:
                    SDL_RenderCopy(renderer, textures->mountain, NULL, &dest_rect);
                    break;
                case WATER:
                    SDL_RenderCopy(renderer, textures->water, NULL, &dest_rect);
                    break;
                default:
                    SDL_RenderCopy(renderer, textures->grass, NULL, &dest_rect);
                    break;
            }
        }
    }
    SDL_RenderPresent(renderer);
}
