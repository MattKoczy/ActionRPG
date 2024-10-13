#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <SDL.h>

// Function prototypes for handling movement and input
void handle_input(SDL_Event event);
void update_player_position(char** map, int map_width, int map_height, int* player_x, int* player_y);
void move_player(char** map, int map_width, int map_height, int* player_x, int* player_y, int dx, int dy);

#endif
