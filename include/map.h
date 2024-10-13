#ifndef MAP_H
#define MAP_H

#define TILE_SIZE 32
#define EMPTY '.'
#define OBSTACLE '#'
#define NPC 'N'
#define PLAYER '@'
#define WATER '~'
#define GRASS '.'

// Function to initialize the map, width, height, and player position
char** init_map(int* map_width, int* map_height, int* player_x, int* player_y);

#endif