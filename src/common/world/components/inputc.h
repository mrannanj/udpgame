#pragma once

#include "common/world/entity_id.h"
#include "client/controller/input/input.h"

struct InputC {
  InputC();
  InputC(const Input&);

  EntityId id;
  unsigned actions;
  float horizontal_angle_delta;
  float vertical_angle_delta;
};
