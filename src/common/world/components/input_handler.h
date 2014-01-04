#pragma once

#include "client/controller/input/input.h"
#include "common/world/entity_id.h"
#include "common/world/components/inputc.h"
#include "common/world/components/physics_system.h"

#include <vector>

class World;

class InputHandler {
public:
  void tick(const std::vector<InputC>&, World&);
};
