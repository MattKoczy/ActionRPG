#ifndef UTILS_H
#define UTILS_H


#include <SDL.h>
#include "textures.h"  // Include Textures struct definition

// Function to control frame rate
void control_fps(Uint32 frame_time);
void cleanup(Textures* textures, SDL_Renderer* renderer, SDL_Window* window, char** map, int map_height);


#endif
