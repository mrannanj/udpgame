#pragma once

#include <SDL.h>

struct Input;

class InputManager {
public:
	InputManager();
	~InputManager();

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	void read_input(Input&) const;

private:
	void init_key_to_action();
	void mouse_button_down(const SDL_Event&, Input&) const;
	void mouse_button_up(const SDL_Event&, Input&) const;
	void mouse_motion(const SDL_Event&, Input&) const;
	void keyup(const SDL_Event&, Input&) const;
	void check_keyboard(Input&) const;
	void check_mouse(Input&) const;

	int m_num_keys;
	Uint8 *m_key_state;
	unsigned *m_key_to_action;
};
