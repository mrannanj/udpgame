#pragma once

#include "common/world/entity_id.h"

class IdGenerator {
public:
  IdGenerator();
  EntityId NextId();

private:
  EntityId next_id_;
};

