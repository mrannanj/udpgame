#pragma once

#include <vector>

#include "client/controller/input/input.h"
#include "common/world/components/inputc.h"
#include "common/world/entity_id.h"
#include "common/world/components/physics_system.h"
#include "common/world/world.h"

class InputSystem {
public:
  void add_input(EntityId, const Input&);
  void add_inputc(const InputC& ic);
  void tick(float, World&);

private:
  std::vector<InputC> m_inputs;
};

extern InputSystem g_input_system;
