#include "client/controller/input/input_manager.h"

#include <iostream>
#include "client/controller/input/input.h"
#include "client/view/window.h"
#include "client/controller/screen_stack.h"

SDLKey binded_keys[] = {
  SDLK_w, SDLK_s, SDLK_d, SDLK_a, SDLK_SPACE, SDLK_LCTRL
};

InputManager::InputManager()
{
  key_state_ = SDL_GetKeyState(&num_keys_);
  //SDL_EnableKeyRepeat(0,0);
  init_actions();
}

InputManager::~InputManager()
{
  delete[] actions_;
}

void InputManager::init_actions() {
  actions_ = new unsigned[num_keys_];
  memset(actions_, 0, sizeof(*actions_) * (unsigned)num_keys_);
  actions_[SDLK_w] = Action::MOVE_FORWARD;
  actions_[SDLK_s] = Action::MOVE_BACK;
  actions_[SDLK_d] = Action::MOVE_RIGHT;
  actions_[SDLK_a] = Action::MOVE_LEFT;
  actions_[SDLK_SPACE] = Action::JUMP;
  actions_[SDLK_LCTRL] = Action::CROUCH;
}

void InputManager::check_mouse(Input& input)
{
  Uint8 mouse_buttons = SDL_GetMouseState(&input.mouse_x_, &input.mouse_y_);
  input.mouse_buttons_ = SDL_BUTTON(1) & mouse_buttons;
  input.gl_mouse_x_ = gl_pos_x(input.mouse_x_);
  input.gl_mouse_y_ = gl_pos_y(input.mouse_y_);
}

void InputManager::ReadInput(Input& i)
{
  memset(&i, 0, sizeof(Input));
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        g_screen_stack.clear();
        break;
      case SDL_KEYDOWN:
        handle_keydown(e, i);
        break;
      case SDL_MOUSEMOTION:
        handle_mouse_motion(e, i);
        break;
    }
  }
  check_keyboard(i);
  check_mouse(i);
}

void InputManager::handle_keydown(SDL_Event& e, Input& i)
{
  if (e.key.keysym.sym == SDLK_ESCAPE)
    i.actions_ |= Action::ESCAPE;
  else if (e.key.keysym.sym == SDLK_F8)
    i.actions_ |= Action::SPAWN_UNIT;
  else if (e.key.keysym.sym == SDLK_TAB)
    i.actions_ |= Action::SWITCH_UNIT;
  else if (e.key.keysym.sym == SDLK_F7)
    i.actions_ |= Action::CAMERA_MODE;
}

void InputManager::handle_mouse_motion(SDL_Event& e, Input &i)
{
  i.mouse_delta_x += e.motion.xrel;
  i.mouse_delta_y += e.motion.yrel;
}

void InputManager::check_keyboard(Input& i)
{
  constexpr size_t n = sizeof(binded_keys)/sizeof(SDLKey);
  for (unsigned k = 0; k < n; ++k) {
    SDLKey key = binded_keys[k];
    if (key_state_[key])
      i.actions_ |= actions_[key];
  }
}

