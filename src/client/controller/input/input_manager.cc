#include "client/controller/input/input_manager.h"

#include "client/view/window.h"
#include "client/controller/input/input.h"
#include "client/controller/screen/screen_stack.h"

#include <iostream>

using namespace std;

SDL_Scancode bound_keys[] = {
	SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_A,
	SDL_SCANCODE_SPACE, SDL_SCANCODE_T, SDL_SCANCODE_1, SDL_SCANCODE_2,
	SDL_SCANCODE_3, SDL_SCANCODE_4, SDL_SCANCODE_5, SDL_SCANCODE_6,
	SDL_SCANCODE_7, SDL_SCANCODE_8, SDL_SCANCODE_9,
};

InputManager::InputManager():
	m_num_keys(0),
	m_key_state(SDL_GetKeyboardState(&m_num_keys)),
	m_key_to_action(nullptr)
{
	m_key_state = SDL_GetKeyboardState(&m_num_keys);
	init_key_to_action();
}

InputManager::~InputManager()
{
	delete[] m_key_to_action;
}

void InputManager::init_key_to_action()
{
	m_key_to_action = new unsigned[m_num_keys];
	memset(m_key_to_action, 0,
	       sizeof(*m_key_to_action) * (unsigned)m_num_keys);
	m_key_to_action[SDL_SCANCODE_W] = ContinousAction::MOVE_FORWARD;
	m_key_to_action[SDL_SCANCODE_S] = ContinousAction::MOVE_BACK;
	m_key_to_action[SDL_SCANCODE_D] = ContinousAction::MOVE_RIGHT;
	m_key_to_action[SDL_SCANCODE_A] = ContinousAction::MOVE_LEFT;
	m_key_to_action[SDL_SCANCODE_T] = ContinousAction::THROW;
	m_key_to_action[SDL_SCANCODE_SPACE] = ContinousAction::JUMP;
	m_key_to_action[SDL_SCANCODE_1] = ContinousAction::ITEM_1;
	m_key_to_action[SDL_SCANCODE_2] = ContinousAction::ITEM_2;
	m_key_to_action[SDL_SCANCODE_3] = ContinousAction::ITEM_3;
	m_key_to_action[SDL_SCANCODE_4] = ContinousAction::ITEM_4;
	m_key_to_action[SDL_SCANCODE_5] = ContinousAction::ITEM_5;
	m_key_to_action[SDL_SCANCODE_6] = ContinousAction::ITEM_6;
	m_key_to_action[SDL_SCANCODE_7] = ContinousAction::ITEM_7;
	m_key_to_action[SDL_SCANCODE_8] = ContinousAction::ITEM_8;
	m_key_to_action[SDL_SCANCODE_9] = ContinousAction::ITEM_9;
}

void InputManager::check_mouse(Input& i) const
{
	Uint8 buttons = SDL_GetMouseState(&i.mouse_x, &i.mouse_y);
	if (buttons & SDL_BUTTON(1)) {
		i.mouse_buttons |= Mouse::LEFT;
		i.continous_actions |= ContinousAction::FIRST;
	}
	if (buttons & SDL_BUTTON(3)) {
		i.mouse_buttons |= Mouse::RIGHT;
		i.continous_actions |= ContinousAction::SECOND;
	}
	if (buttons & SDL_BUTTON(2))
		i.mouse_buttons |= Mouse::MIDDLE;

	i.gl_mouse_x = gl_pos_x(i.mouse_x);
	i.gl_mouse_y = gl_pos_y(i.mouse_y);
}

void InputManager::read_input(Input& i) const
{
	i.clear_consumables();
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			g_screen_stack.clear();
			break;
		case SDL_KEYUP:
			keyup(e, i);
			break;
		case SDL_KEYDOWN:
			i.keydown_scancode = e.key.keysym.scancode;
			i.keydown_symbol = e.key.keysym.sym;
			break;
		case SDL_MOUSEMOTION:
			mouse_motion(e, i);
			break;
		case SDL_MOUSEBUTTONUP:
			mouse_button_up(e, i);
			break;
		case SDL_WINDOWEVENT:
			handle_window_event(e.window);
			break;
		}
	}
	check_keyboard(i);
	check_mouse(i);
}

void InputManager::handle_window_event(const SDL_WindowEvent& w) const
{
	switch (w.event) {
	case SDL_WINDOWEVENT_SIZE_CHANGED:
		window_width = w.data1;
		window_height = w.data2;
		glViewport(0, 0, window_width, window_height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		break;
	}
}

void InputManager::mouse_button_up(const SDL_Event& e, Input& i) const
{
	switch (e.button.button) {
	case SDL_BUTTON_LEFT:
		i.mouse_buttons &= ~(Mouse::LEFT);
		i.mouse_click |= Mouse::LEFT;
		break;
	case SDL_BUTTON_RIGHT:
		i.mouse_buttons &= ~(Mouse::RIGHT);
		i.mouse_click |= Mouse::RIGHT;
		break;
	case SDL_BUTTON_MIDDLE:
		i.mouse_buttons &= ~(Mouse::MIDDLE);
		i.mouse_click |= Mouse::MIDDLE;
		break;
	}
}

void InputManager::keyup(const SDL_Event& e, Input& i) const
{
	switch (e.key.keysym.sym) {
	case SDLK_ESCAPE:
		i.keypress |= DiscreteAction::ESCAPE;
		break;
	case SDLK_TAB:
		i.continous_actions |= ContinousAction::PLAYER_MODE;
		break;
	case SDLK_F8:
		i.continous_actions |= ContinousAction::SPAWN_MONSTER;
		break;
	case SDLK_g:
		i.keypress |= DiscreteAction::TOGGLE_MOUSEGRAB;
		break;
	default:
		break;
	}
}

void InputManager::mouse_motion(const SDL_Event& e, Input& i) const
{
	i.mouse_delta_x += e.motion.xrel;
	i.mouse_delta_y += e.motion.yrel;
}

void InputManager::check_keyboard(Input& i) const
{
	constexpr size_t n = sizeof(bound_keys) / sizeof(SDL_Keycode);
	for (unsigned k = 0; k < n; ++k) {
		SDL_Scancode scancode = bound_keys[k];
		if (m_key_state[scancode])
			i.continous_actions |= m_key_to_action[scancode];
	}
}
