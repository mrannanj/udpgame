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
  mPhysicsHandler.add(&p);
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
  mPhysicsHandler.setObjects(w);
  mGrid.setGrid(w);
  mTickNumber = w.tick_number();
  mInit = true;
}

WorldState World::getState() {
  WorldState w;
  mPhysicsHandler.getObjects(w);
  mGrid.getGrid(w);
  w.set_tick_number(mTickNumber);
  return w;
}
