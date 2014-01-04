#include "common/world/world.h"
#include "common/world/components/input_handler.h"
#include "common/world/components/physics_handler.h"
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

World::World():
  mInit(false),
  mTickNumber(0)
{
}

void World::defaultWorld() {
  g_grid.defaultGrid();
}

EntityId World::spawn_entity(int fd) {
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
  mClient2Entity[fd] = p.id;
  return p.id;
}

int World::tick(float dt, const std::vector<InputC>& inputs) {
  mInputHandler.tick(inputs, *this);
  g_physics_system.tick(dt);
  removeDead();
  return ++mTickNumber;
}

void World::removeDead() {
  for (EntityId id : g_physics_system.mRemoveList) {
    g_physics_system.remove(id);
  }
}

void World::setState(const WorldState& w) {
  g_physics_system.clear();
  for (int i = 0; i < w.object_size(); ++i) {
    const Object& o = w.object(i);
    PhysicsC p;
    p.id = o.id();
    p.position.x = o.x();
    p.position.y = o.y();
    p.position.z = o.z();
    p.vertical_angle = o.vertical_angle();
    p.horizontal_angle = o.horizontal_angle();
    p.dimensions = glm::vec3(0.4f, 0.9f, 0.4f);
    p.update_bbs();
    g_physics_system.add(p);
  }
  mTickNumber = w.tick_number();
  memcpy(g_grid.mGrid.mData, w.grid().c_str(), 1000);
  mInit = true;
}

WorldState World::getState() {
  WorldState w;
  for (const PhysicsC& p : g_physics_system.physics_components()) {
    Object* o = w.add_object();
    o->set_id(p.id);
    o->set_x(p.position.x);
    o->set_y(p.position.y);
    o->set_z(p.position.z);
    o->set_vertical_angle(p.vertical_angle);
    o->set_horizontal_angle(p.horizontal_angle);
  }
  w.set_grid(g_grid.mGrid.mData, 1000);
  w.set_tick_number(mTickNumber);
  return w;
}
