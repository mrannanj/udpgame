#ifndef COMMON_WORLD_ID_GENERATOR_H
#define COMMON_WORLD_ID_GENERATOR_H

#include "common/google.h"
#include "common/world/entity_id.h"

class IdGenerator {
public:
  IdGenerator();
  EntityId NextId();

private:
  DISALLOW_COPY_AND_ASSIGN(IdGenerator);
  EntityId next_id_;
};

#endif

