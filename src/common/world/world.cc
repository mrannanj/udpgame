#include "common/world/world.h"
#include "common/world/components/input_system.h"
#include "common/world/components/physics_system.h"
#include "common/world/components/physics.h"
#include "common/world/components/grid.h"

#include <SDL.h>
#include <GL/glew.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <random>
#include <chrono>
#include <set>

using namespace std;

World::World()
{
}

void World::defaultWorld() {
  g_grid.defaultGrid();
}

void World::spawn_entity() {
  cout << "spawning unit" << endl;
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine g(seed);
  uniform_real_distribution<double> d(1.0f, 10.0f);

  PhysicsC p;
  memset(&p, 0, sizeof(p));
  p.id = m_idgen.NextId();
  p.position = glm::vec3(d(g), d(g), d(g));
  p.dimensions = glm::vec3(0.4f, 0.9f, 0.4f);
  p.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  g_physics_system.add(p);
}

void World::tick(float dt, const ClientInput& ci) {
  setInput(ci);
  g_input_system.tick(dt, *this);
  g_physics_system.tick(dt);
  removeDead();
}

void World::removeDead() {
  for (EntityId id : g_physics_system.mRemoveList) {
    g_physics_system.remove(id);
  }
}

void World::handleAMessage(const AMessage& a) {
  switch (a.type()) {
    case Type::WORLD_STATE:
      setState(a.world_state());
      break;
    case Type::CLIENT_INPUT:
      cout << "deprecated handlemessage" << endl;
      break;
  }
}

void World::setInput(const ClientInput& ci) {
  InputC ic(ci);
  ic.id = 0;
  g_input_system.add_inputc(ic);
}

void World::setState(const WorldState& w) {
  g_physics_system.clear();
  for (int i = 0; i < w.object_size(); ++i) {
    const Object& o = w.object(i);
    PhysicsC p;
    p.position.x = o.x();
    p.position.y = o.y();
    p.position.z = o.z();
    p.dimensions = glm::vec3(0.4f, 0.9f, 0.4f);
    p.update_bbs();
    g_physics_system.add(p);
  }
  memcpy(g_grid.m_grid, w.grid().c_str(), 1000);
}

WorldState World::getState() {
  WorldState w;
  for (const PhysicsC& p : g_physics_system.physics_components()) {
    Object* o = w.add_object();
    o->set_x(p.position.x);
    o->set_y(p.position.y);
    o->set_z(p.position.z);
  }
  w.set_grid(g_grid.m_grid, 1000);
  return w;
}
