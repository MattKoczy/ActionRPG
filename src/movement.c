#include <SDL.h>
#include <stdbool.h>
#include "movement.h"
#include "map.h"

static bool move_up, move_down, move_left, move_right;

void handle_input(SDL_Event event) {
    bool key_down = event.type == SDL_KEYDOWN;
    switch (event.key.keysym.sym) {
        case SDLK_w: move_up = key_down; break;
        case SDLK_s: move_down = key_down; break;
        case SDLK_a: move_left = key_down; break;
        case SDLK_d: move_right = key_down; break;
    }
}

void move_player(char** map, int map_width, int map_height, int* player_x, int* player_y, int dx, int dy) {
    int new_x = *player_x + dx;
    int new_y = *player_y + dy;

    if (new_x >= 0 && new_x < map_width && new_y >= 0 && new_y < map_height) {
        if (map[new_y][new_x] == EMPTY) {
            map[*player_y][*player_x] = EMPTY;
            *player_x = new_x;
            *player_y = new_y;
            map[*player_y][*player_x] = PLAYER;
        }
    }
}

void update_player_position(char** map, int map_width, int map_height, int* player_x, int* player_y) {
    if (move_up) move_player(map, map_width, map_height, player_x, player_y, 0, -1);
    if (move_down) move_player(map, map_width, map_height, player_x, player_y, 0, 1);
    if (move_left) move_player(map, map_width, map_height, player_x, player_y, -1, 0);
    if (move_right) move_player(map, map_width, map_height, player_x, player_y, 1, 0);
}
