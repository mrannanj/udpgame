#include "common/world/world.h"
#include "common/world/components/physics.h"
#include "common/world/components/grid_handler.h"

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
  mGrid.defaultGrid();
}

EntityId World::spawn_entity(int fd) {
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine g(seed);
  uniform_real_distribution<double> d(1.0f, 10.0f);

  PhysicsC p;
  memset(&p, 0, sizeof(p));
  p.id = m_idgen.NextId();
  p.position = glm::vec3(d(g), d(g), d(g));
  p.dimensions = glm::vec3(0.4f, 0.9f, 0.4f);
  p.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  mPhysicsHandler.add(p);
  mClient2Entity[fd] = p.id;
  return p.id;
}

int World::tick(float dt, const std::vector<InputC>& inputs) {
  mInputHandler.tick(inputs, *this);
  mPhysicsHandler.tick(dt, *this);
  removeDead();
  return ++mTickNumber;
}

void World::removeDead() {
  for (EntityId id : mPhysicsHandler.mRemoveList) {
    mPhysicsHandler.remove(id);
  }
}

PhysicsHandler& World::physics() {
  return mPhysicsHandler;
}

GridHandler& World::grid() {
  return mGrid;
}

void World::setState(const WorldState& w) {
  mPhysicsHandler.clear();
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
    mPhysicsHandler.add(p);
  }
  mTickNumber = w.tick_number();
  memcpy(mGrid.mGrid.mData, w.grid().c_str(), 1000);
  mInit = true;
}

WorldState World::getState() {
  WorldState w;
  for (const PhysicsC& p : mPhysicsHandler.physics_components()) {
    Object* o = w.add_object();
    o->set_id(p.id);
    o->set_x(p.position.x);
    o->set_y(p.position.y);
    o->set_z(p.position.z);
    o->set_vertical_angle(p.vertical_angle);
    o->set_horizontal_angle(p.horizontal_angle);
  }
  w.set_grid(mGrid.mGrid.mData, 1000);
  w.set_tick_number(mTickNumber);
  return w;
}
