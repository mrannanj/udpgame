#ifndef CLIENT_CONTROLLER_INPUT_INPUT_H
#define CLIENT_CONTROLLER_INPUT_INPUT_H

namespace Action {
  enum Enum {
    NONE = 0,
    ESCAPE = 1,
    MOVE_LEFT = 2,
    MOVE_RIGHT = 4,
    MOVE_FORWARD = 8,
    MOVE_BACK = 16
  };
}

struct Input {
  unsigned actions_;
  int mouse_buttons_;
  int mouse_x_;
  int mouse_y_;
  float gl_mouse_x_;
  float gl_mouse_y_;
};

#endif
