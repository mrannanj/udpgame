#include "client/input/input_reader.h"

#include <iostream>
#include "client/input/input.h"
#include "client/view/window.h"

InputReader::InputReader() {}

void InputReader::Init()
{
  key_state_ = SDL_GetKeyState(&num_keys_);
  actions_ = new unsigned[num_keys_];
  SDL_EnableKeyRepeat(0,0);
}

void InputReader::Destroy() {
  delete[] actions_;
}

void InputReader::CheckMouseState(Input& input) {
  SDL_GetMouseState(&input.mouse_x_, &input.mouse_y_);
  input.gl_mouse_x_ = gl_pos_x(input.mouse_x_);
  input.gl_mouse_y_ = gl_pos_y(input.mouse_y_);
}

bool InputReader::ReadInput(Input& i) {
  memset(&i, 0, sizeof(Input));
  bool quit = false;
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        quit = true;
        break;
    }
  }
  CheckMouseState(i);
  return quit;
}

