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
  EntityId eid = m_idgen.NextId();

  PhysicsC p;
  memset(&p, 0, sizeof(p));

  p.entityid = eid;
  p.position = spawn_position;
  p.dimensions = glm::vec3(0.4f, 0.2f, 0.4f);
  p.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  mPhysicsHandler.add(p);
}

void World::spawn_player(int clientid) {
  EntityId eid = m_idgen.NextId();

  PhysicsC p;
  memset(&p, 0, sizeof(p));

  p.entityid = eid;
  p.position = spawn_position;
  p.dimensions = glm::vec3(0.4f, 0.9f, 0.4f);
  p.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  mPhysicsHandler.add(p);

  Inventory i;
  i.set_eid(eid);
  i.set_wielding(1);
  mInventory.add(i);

  ClientData* cd = mClient.getByClient(clientid);
  assert(cd != nullptr);
  cd->set_dead(0);
  cd->set_eid(eid);
  cd->set_mode(ClientMode::PLAYER);
}

int World::tick(float dt, const FrameInputs& fis) {
  mDeleteList.clear();
  mInputHandler.deserialize(fis.frame_inputs());

  mInputHandler.tick(dt, *this);
  mClient.tick(dt, *this);
  mPhysicsHandler.tick(dt, *this);
  mInventory.tick(dt, *this);

  removeDead();
  return ++mTickNumber;
}

void World::removeDead() {
  mClient.handleDead(mDeleteList);
  mPhysicsHandler.handleDead(mDeleteList);
  mInventory.handleDead(mDeleteList);
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

ClientHandler& World::client() {
  return mClient;
}

InputHandler& World::input() {
  return mInputHandler;
}

InitialState World::getInitialState() {
  InitialState i;
  mGrid.serialize(i);
  mClient.serialize(i.mutable_client_data());
  mInventory.serialize(i.mutable_inventories());
  mPhysicsHandler.serialize(i.mutable_physics_data());
  return i;
}

void World::setInitialState(const InitialState& i) {
  mGrid.deserialize(i);
  mClient.deserialize(i.client_data());
  mInventory.deserialize(i.inventories());
  mPhysicsHandler.deserialize(i.physics_data());
  mInit = true;
}
