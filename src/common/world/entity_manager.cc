
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
}

void EntityManager::spawn_entity()
{
  PhysicsC p;
  memset(&p, 0, sizeof(p));
  p.id = m_idgen.NextId();
  p.position = glm::vec3(3.0f, 5.0f, 1.0f);
  p.dimensions = glm::vec3(0.4f, 0.9f, 0.4f);
  p.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  g_physics_system.add(p);
  std::cout << "spawned entity " << p.id << " at "
    << "(" << p.position.x << "," << p.position.y << "," << p.position.z << ")"
    << std::endl;
}

void EntityManager::tick(float dt)
{
  g_physics_system.tick(dt);
  g_input_system.tick(dt);
}
