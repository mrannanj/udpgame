#include "client/controller/input/input.h"

bool Input::consume_mouse_click(Mouse::Enum button) {
  if (mouse_click & button) {
    mouse_click &= ~button;
    return true;
  }
  return false;
}

bool Input::consume_discrete_action(DiscreteAction::Enum action) {
  if (keypress & action) {
    keypress &= ~action;
    return true;
  }
  return false;
}

void Input::clear_consumables() {
  mouse_click = 0;
  keypress = 0;
  keydown_symbol = -1;
  mouse_delta_x = 0;
  mouse_delta_y = 0;
  continous_actions = 0;
}
