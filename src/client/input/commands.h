#ifndef CLIENT_COMMANDS_H
#define CLIENT_COMMANDS_H

namespace Commands {
enum Enum {
  NONE = 0,
  QUIT = 1,
  MOVE_LEFT = 2,
  MOVE_RIGHT = 4,
  MOVE_FORWARD = 8,
  MOVE_BACK = 16,
};
}

struct Actions {
  unsigned actions;
};

#endif

