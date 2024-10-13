#include "map.h"
#include <stdlib.h>

char** init_map(int* map_width, int* map_height, int* player_x, int* player_y) {
    *map_width = 8 + rand() % 8;    // Set map width between 8 and 15
    *map_height = 8 + rand() % 8;   // Set map height between 8 and 15
    
    // Allocate memory for the map
    char** map = malloc(*map_height * sizeof(char*));
    for (int i = 0; i < *map_height; i++) {
        map[i] = malloc(*map_width * sizeof(char));
        for (int j = 0; j < *map_width; j++) {
            map[i][j] = EMPTY;  // Initialize all tiles as EMPTY
        }
    }

    // Place obstacles randomly
    for (int i = 0; i < (*map_width * *map_height) / 8; i++) {
        int x = rand() % *map_width;
        int y = rand() % *map_height;
        map[y][x] = OBSTACLE;
    }

    // Place NPCs randomly
    for (int i = 0; i < 3; i++) {
        int x = rand() % *map_width;
        int y = rand() % *map_height;
        if (map[y][x] == EMPTY) {
            map[y][x] = NPC;
        }
    }

    // Set player position at a random empty spot
    do {
        *player_x = rand() % *map_width;
        *player_y = rand() % *map_height;
    } while (map[*player_y][*player_x] != EMPTY);
    map[*player_y][*player_x] = PLAYER;

    return map;
}