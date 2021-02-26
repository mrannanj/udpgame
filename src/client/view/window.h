#pragma once

#include <SDL2/SDL.h>

float gl_pos_x(int);
float gl_pos_y(int);
void open_window(bool, SDL_Window**, SDL_Renderer**);
void grab_mouse();
void release_mouse();
void toggle_mousegrab();

extern int window_width;
extern int window_height;
