#pragma once

#include <SDL2/SDL.h>

namespace ContinousAction {
	enum Enum : unsigned {
		MOVE_LEFT = 1,
		MOVE_RIGHT = 2,
		MOVE_FORWARD = 4,
		MOVE_BACK = 8,
		JUMP = 16,
		PLAYER_MODE = 32,
		FIRST = 64,
		SECOND = 128,
		ITEM_1 = 1 << 8,
		ITEM_2 = 1 << 9,
		ITEM_3 = 1 << 10,
		ITEM_4 = 1 << 11,
		ITEM_5 = 1 << 12,
		ITEM_6 = 1 << 13,
		ITEM_7 = 1 << 14,
		ITEM_8 = 1 << 15,
		ITEM_9 = 1 << 16,
		SPAWN_MONSTER = 1 << 17,
		THROW = 1 << 18
	};
}

namespace DiscreteAction {
	enum Enum : unsigned {
		ESCAPE = 1,
		TOGGLE_MOUSEGRAB = 2
	};
}

namespace Mouse {
	enum Enum : unsigned {
		LEFT = 1,
		RIGHT = 2,
		MIDDLE = 4
	};
}

struct Input {
	unsigned mouse_click;
	unsigned continous_actions;
	unsigned keypress;
	SDL_Scancode keydown_scancode;
	SDL_Keycode keydown_symbol;
	unsigned mouse_buttons;
	int mouse_x;
	int mouse_y;
	int mouse_delta_x;
	int mouse_delta_y;
	float gl_mouse_x;
	float gl_mouse_y;

	void clear_consumables();
	bool consume_mouse_click(Mouse::Enum);
	bool consume_discrete_action(DiscreteAction::Enum);
};
