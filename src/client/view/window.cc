#include "common/platform.h"
#include "client/view/window.h"

#include <SDL2/SDL.h>

int window_width = 0;
int window_height = 0;
static bool sMouseGrab = false;

void open_window(bool fullscreen, SDL_Window **window, SDL_Renderer **renderer)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Uint32 f = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	if (fullscreen) {
		f |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	} else {
		window_width = 800;
		window_height = 600;
	}
	*window = SDL_CreateWindow("udpgame", SDL_WINDOWPOS_UNDEFINED,
				  SDL_WINDOWPOS_UNDEFINED,
				  window_width, window_height, f);
	*renderer = SDL_CreateRenderer(*window, -1, 0);

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(.0f, .0f, .0f, .0f);
}

float gl_pos_x(int x)
{
	return ((float) x / (window_width / 2)) - 1.0f;
}

float gl_pos_y(int y)
{
	return 1.0f - (float) y / (window_height / 2);
}

void toggle_mousegrab()
{
	sMouseGrab ? release_mouse() : grab_mouse();
}

void grab_mouse()
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	sMouseGrab = true;
}

void release_mouse()
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	sMouseGrab = false;
}
