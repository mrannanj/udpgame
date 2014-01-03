#include "client/controller/input/input_manager.h"

#include <iostream>
#include "client/controller/input/input.h"
#include "client/view/window.h"
#include "client/controller/screen_stack.h"

using namespace std;

SDLKey binded_keys[] = {
  SDLK_w, SDLK_s, SDLK_d, SDLK_a, SDLK_SPACE
};

InputManager::InputManager() {
  m_key_state = SDL_GetKeyState(&m_num_keys);
  SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL*6);
  SDL_EnableUNICODE(1);
  init_key_to_action();
}

InputManager::~InputManager() {
  delete[] m_key_to_action;
}

void InputManager::init_key_to_action() {
  m_key_to_action = new unsigned[m_num_keys];
  memset(m_key_to_action, 0, sizeof(*m_key_to_action) * (unsigned)m_num_keys);
  m_key_to_action[SDLK_w] = ContinousAction::MOVE_FORWARD;
  m_key_to_action[SDLK_s] = ContinousAction::MOVE_BACK;
  m_key_to_action[SDLK_d] = ContinousAction::MOVE_RIGHT;
  m_key_to_action[SDLK_a] = ContinousAction::MOVE_LEFT;
  m_key_to_action[SDLK_SPACE] = ContinousAction::JUMP;
}

void InputManager::check_mouse(Input& i) const {
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

void InputManager::read_input(Input& i) const {
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
        i.keydown_symbol = e.key.keysym.unicode;
        break;
      case SDL_MOUSEMOTION:
        mouse_motion(e, i);
        break;
      case SDL_MOUSEBUTTONUP:
        mouse_button_up(e, i);
        break;
    }
  }
  check_keyboard(i);
  check_mouse(i);
}

void InputManager::mouse_button_up(const SDL_Event& e, Input& i) const {
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

void InputManager::keyup(const SDL_Event& e, Input& i) const {
  switch (e.key.keysym.sym) {
    case SDLK_ESCAPE:
      i.keypress |= DiscreteAction::ESCAPE;
      break;
    case SDLK_F8:
      i.continous_actions |= ContinousAction::SPAWN_UNIT;
      break;
    case SDLK_F7:
      i.keypress |= DiscreteAction::SWITCH_CAMERA_MODE;
      break;
    case SDLK_TAB:
      i.keypress |= DiscreteAction::SWITCH_UNIT;
      break;
    case SDLK_g:
      i.keypress |= DiscreteAction::TOGGLE_MOUSEGRAB;
      break;
    default:
      break;
  }
}

void InputManager::mouse_motion(const SDL_Event& e, Input &i) const {
  i.mouse_delta_x += e.motion.xrel;
  i.mouse_delta_y += e.motion.yrel;
}

void InputManager::check_keyboard(Input& i) const {
  constexpr size_t n = sizeof(binded_keys)/sizeof(SDLKey);
  for (unsigned k = 0; k < n; ++k) {
    SDLKey key = binded_keys[k];
    if (m_key_state[key])
      i.continous_actions |= m_key_to_action[key];
  }
}

