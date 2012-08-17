#ifndef COMMON_WORLD_COMPONENTS_INPUTC_H
#define COMMON_WORLD_COMPONENTS_INPUTC_H

#include "common/world/entity_id.h"

struct InputC
{
  EntityId id;
  unsigned actions;
  float horizontal_angle_delta;
  float vertical_angle_delta;
};

#endif
