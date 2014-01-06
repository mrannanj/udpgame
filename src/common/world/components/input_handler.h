#pragma once

#include "common/world/entity_id.h"
#include "common/world/components/inputc.h"
#include "common/world/components/world_handler.h"

#include <vector>

struct InputHandler : public WorldHandler<InputC> {
  void setInputs(const std::vector<InputC>&);
  InputC* getByClient(int);
};
