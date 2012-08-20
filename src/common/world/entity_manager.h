#ifndef COMMON_WORLD_ENTITY_MANAGER_H
#define COMMON_WORLD_ENTITY_MANAGER_H

#include <map>
#include "common/google.h"
#include "common/world/components/physics_system.h"
#include "common/world/id_generator.h"

class EntityManager
{
public:
  EntityManager();
  DISALLOW_COPY_AND_ASSIGN(EntityManager);

  void tick(float);
  void spawn_entity();

private:
  IdGenerator m_idgen;
};

#endif

