#pragma once

#include "common/world/entity_id.h"
#include "common/world/components/inputc.h"

#include <vector>

class World;

class InputHandler {
public:
  void tick(const std::vector<InputC>&, World&);
};
