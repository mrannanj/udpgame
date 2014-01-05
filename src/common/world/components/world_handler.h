#pragma once

#include "common/world/entity_id.h"

class World;

class WorldHandler {
public:
  virtual void* get(EntityId) = 0;
  virtual void tick(float, World&) = 0;
  virtual void add(void*) = 0;
  virtual ~WorldHandler() {};
};
