#include "common/world/world.h"
#include "common/world/components/physics.h"
#include "common/world/components/grid_handler.h"

#include <SDL.h>
#include <GL/glew.h>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>
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

void World::spawn_monster() {
  PhysicsC p;
  memset(&p, 0, sizeof(p));
  p.id = m_idgen.NextId();
  p.position = spawn_position;
  p.dimensions = glm::vec3(0.4f, 0.2f, 0.4f);
  p.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  mPhysicsHandler.add(p);
}

void World::spawn_player(int fd) {
  PhysicsC p;
  memset(&p, 0, sizeof(p));
  p.id = m_idgen.NextId();
  p.position = spawn_position;
  p.dimensions = glm::vec3(0.4f, 0.9f, 0.4f);
  p.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  mPhysicsHandler.add(p);

  Inventory i;
  i.id = p.id;
  i.mWielding = 1;
  mInventory.add(i);

  mClient2Entity[fd] = p.id;
}

int World::tick(float dt, const std::vector<InputC>& inputs) {
  mDeleteList.clear();
  mInputHandler.tick(inputs, *this);
  mPhysicsHandler.tick(dt, *this);
  removeDead();
  return ++mTickNumber;
}

void World::removeDead() {
  mPhysicsHandler.removeComponents(mDeleteList);
}

InventoryHandler& World::inventory() {
  return mInventory;
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
