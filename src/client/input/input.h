#ifndef CLIENT_INPUT_INPUT_H
#define CLIENT_INPUT_INPUT_H

namespace Action {
enum Enum {
  NONE = 0,
  MOVE_LEFT = 1,
  MOVE_RIGHT = 2,
  MOVE_FORWARD = 4,
  MOVE_BACK = 8,
};
}

struct Input {
  unsigned actions_;
  int mouse_x_;
  int mouse_y_;
  float gl_mouse_x_;
  float gl_mouse_y_;
};

#endif
