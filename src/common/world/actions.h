#ifndef COMMON_WORLD_ACTIONS_H
#define COMMON_WORLD_ACTIONS_H

namespace Action {
enum Enum {
  MOVE_LEFT = 1,
  MOVE_RIGHT = 2,
  MOVE_FORWARD = 4,
  MOVE_BACK = 8,
};
}

struct Actions {
  unsigned commands;
};

#endif

