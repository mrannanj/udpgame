#include <SDL.h>

#include "common/platform.h"
#include "client/view/window.h"

int window_width = 0;
int window_height = 0;
static bool sMouseGrab = false;

void open_window(bool fullscreen) {
  SDL_Init(SDL_INIT_EVERYTHING);
  Uint32 f = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL;

  if (fullscreen) {
    f |= SDL_FULLSCREEN;
  } else {
    window_width = 800;
    window_height = 600;
  }
  SDL_Surface* surface = SDL_SetVideoMode(window_width, window_height, 32, f);
  window_width = surface->w;
  window_height = surface->h;

  SDL_WM_SetCaption("udpgame", 0);

  glewExperimental = GL_TRUE;
  glewInit();

  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

float gl_pos_x(int x) {
  return ((float)x / (window_width/2)) - 1.0f;
}

float gl_pos_y(int y) {
  return 1.0f - (float)y / (window_height/2);
}

void toggle_mousegrab() {
  sMouseGrab ? release_mouse() : grab_mouse();
}

void grab_mouse() {
  SDL_WM_GrabInput(SDL_GRAB_ON);
  SDL_ShowCursor(SDL_DISABLE);
  sMouseGrab = true;
}

void release_mouse() {
  SDL_WM_GrabInput(SDL_GRAB_OFF);
  SDL_ShowCursor(SDL_ENABLE);
  sMouseGrab = false;
}
