#ifndef CLIENT_CONTROLLER_INPUT_MANAGER_H
#define CLIENT_CONTROLLER_INPUT_MANAGER_H

#include <SDL.h>

#include "common/google.h"

struct Input;

//! InputReader translates input from keyboard and mouse to in-game commands.
class InputManager
{
	public:
	InputManager();
	~InputManager();
	DISALLOW_COPY_AND_ASSIGN(InputManager);

	void ReadInput(Input&);

	private:

	void init_actions();
	void handle_mouse_motion(SDL_Event&, Input&);
	void handle_keydown(SDL_Event&, Input&);
	void check_keyboard(Input&);
	void check_mouse(Input&);

	int num_keys_;
	Uint8* key_state_;
  unsigned* actions_;
};

#endif
