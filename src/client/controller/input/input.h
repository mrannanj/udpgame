#ifndef CLIENT_CONTROLLER_INPUT_INPUT_H
#define CLIENT_CONTROLLER_INPUT_INPUT_H

namespace Action {
  enum Enum {
    NONE = 0,
    ESCAPE = 1,
    MOVE_LEFT = 2,
    MOVE_RIGHT = 4,
    MOVE_FORWARD = 8,
    MOVE_BACK = 16,
    JUMP = 32,
    CROUCH = 64,
    SPAWN_UNIT = 128,
    SWITCH_UNIT = 256,
    CAMERA_MODE = 512
  };
}

struct Input {
  bool escape;
  unsigned actions_;
  int mouse_buttons_;
  int mouse_x_;
  int mouse_y_;
  int mouse_delta_x;
  int mouse_delta_y;
  float gl_mouse_x_;
  float gl_mouse_y_;
};

#endif
