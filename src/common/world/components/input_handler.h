#pragma once

#include "common/world/entity_id.h"
#include "common/world/components/inputc.h"
#include "common/world/components/world_handler.h"

#include <vector>

class World;

class InputHandler : public WorldHandler<InputC> {
public:
  void setInputs(const std::vector<InputC>&);
  void tick(float, World&);
};
