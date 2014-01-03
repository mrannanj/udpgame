#pragma once

namespace ContinousAction {
  enum Enum : unsigned {
    MOVE_LEFT = 1,
    MOVE_RIGHT = 2,
    MOVE_FORWARD = 4,
    MOVE_BACK = 8,
    JUMP = 16,
    SPAWN_UNIT = 32,
    FIRST = 64,
    SECOND = 128
  };
}

namespace DiscreteAction {
  enum Enum : unsigned {
    ESCAPE = 1,
    SWITCH_UNIT = 4,
    SWITCH_CAMERA_MODE = 8,
    TOGGLE_MOUSEGRAB = 16
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
  int keydown_symbol;
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
