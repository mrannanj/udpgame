#ifndef COMMON_WORLD_COMPONENTS_INPUT_SYSTEM_H
#define COMMON_WORLD_COMPONENTS_INPUT_SYSTEM_H

#include <vector>

#include "client/controller/input/input.h"
#include "common/world/components/inputc.h"
#include "common/world/entity_id.h"
#include "common/world/components/physics_system.h"

class InputSystem
{
public:
  void add_input(EntityId, const Input&);
  void tick(float);

private:
  std::vector<InputC> m_inputs;
};

extern InputSystem g_input_system;

#endif
