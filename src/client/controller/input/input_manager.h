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

	void read_input(Input&) const;

	private:

	void init_key_to_action();
	void mouse_button_down(const SDL_Event&, Input&) const;
	void mouse_button_up(const SDL_Event&, Input&) const;
	void mouse_motion(const SDL_Event&, Input&) const;
	//void keydown(const SDL_Event&, Input&) const;
	void keyup(const SDL_Event&, Input&) const;
	void check_keyboard(Input&) const;
	void check_mouse(Input&) const;

	int m_num_keys;
	Uint8* m_key_state;
  unsigned* m_key_to_action;
};

#endif
