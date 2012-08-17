
#include <SDL.h>
#include <GL/glew.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>

#include "common/world/entity_manager.h"
#include "common/world/components/input_system.h"
#include "common/world/components/physics_system.h"

EntityManager::EntityManager()
{
  memset(m_blocks, 0, WORLD_MAX_X*WORLD_MAX_Y*WORLD_MAX_Z);
  for (unsigned x = 0; x < WORLD_MAX_X; ++x)
    for (unsigned z = 0; z < WORLD_MAX_Z; ++z)
      m_blocks[x][0][z] = x % 4 + z % 2;
}

void EntityManager::spawn_entity()
{
  PhysicsC p;
  memset(&p, 0, sizeof(p));
  p.id = m_idgen.NextId();
  g_physics_system.add(p);
  std::cout << "spawned entity " << p.id << " at "
    << "(" << p.position.x << "," << p.position.y << "," << p.position.z << ")"
    << std::endl;
}

void EntityManager::tick(float dt)
{
  g_input_system.tick(dt);
  g_physics_system.tick(dt);
}
