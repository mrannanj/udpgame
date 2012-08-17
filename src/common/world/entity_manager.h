#ifndef COMMON_WORLD_ENTITY_MANAGER_H
#define COMMON_WORLD_ENTITY_MANAGER_H

#include <map>
#include "common/google.h"
#include "common/world/components/physics_system.h"
#include "common/world/id_generator.h"

#define WORLD_MAX_X 25
#define WORLD_MAX_Y 25
#define WORLD_MAX_Z 25

class EntityManager
{
public:
  EntityManager();
  DISALLOW_COPY_AND_ASSIGN(EntityManager);

  void tick(float);
  void spawn_entity();

  char m_blocks[WORLD_MAX_X][WORLD_MAX_Y][WORLD_MAX_Z];

private:
  IdGenerator m_idgen;
};

#endif

