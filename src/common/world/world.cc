#include "common/config.h"
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
#include <cstdlib>

using namespace std;

World::World(bool init):
  mInit(init),
  mTickNumber(0),
  mHash(0)
{
  if (mInit) mGrid.defaultGrid();
  updateHash();
}

unsigned World::hash() const {
  return mHash;
}

void World::updateHash() {
  mHash = mPhysicsHandler.hash();
}

void World::throw_object(const Physics& o, ObjectType t) {
  EntityId eid = m_idgen.generateId();

  Physics p;
  memset(&p, 0, sizeof(p));

  p.entityid = eid;
  p.position = o.eye_position() + o.look_direction() * 2.0f;
  p.half_dim = glm::vec3(0.2f, 0.2f, 0.2f);
  p.velocity = o.look_direction() * 10.0f;
  p.type = t;
  mPhysicsHandler.add(p);

  Lifetime l;
  l.set_eid(eid);
  l.set_ttl(10.0f);
  mLifetime.add(l);
}

void World::onBlockDestruction(int x, int y, int z) {
  char& b = mGrid.mArr.getRef(x,y,z);

  EntityId eid = m_idgen.generateId();

  Physics p;
  memset(&p, 0, sizeof(p));

  p.entityid = eid;
  p.position = glm::vec3((float)x,(float)y,(float)z) + 0.5f;
  p.half_dim = glm::vec3(0.2f, 0.2f, 0.2f);
  p.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  p.type = (ObjectType)b;
  mPhysicsHandler.add(p);
  b = 0;

  Lifetime l;
  l.set_eid(eid);
  l.set_ttl(10.0f);
  mLifetime.add(l);
}

void World::spawn_player(int clientid) {
  EntityId eid = m_idgen.generateId();

  Physics p;
  memset(&p, 0, sizeof(p));

  p.entityid = eid;
  p.position = mGrid.spawn_pos();
  p.half_dim = glm::vec3(0.4f, 0.9f, 0.4f);
  p.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  p.type = ObjectType::PLAYER;
  mPhysicsHandler.add(p);

  Inventory i;
  i.entityid = eid;
  i.wielding = ObjectType::GRASS;
  mInventory.add(i);

  ClientData* cd = mClient.getByClient(clientid);
  assert(cd != nullptr);
  cd->set_dead(0);
  cd->set_eid(eid);
  cd->set_mode(ClientMode::MODE_PLAYER);
}

void World::tick(const FrameInputs& fis) {
  float dt = secs_per_tick;

  mDeleteList.clear();
  mInputHandler.deserialize(fis.frame_inputs());

  mInputHandler.tick(dt, *this);
  mClient.tick(dt, *this);
  mPhysicsHandler.tick(dt, *this);
  mInventory.tick(dt, *this);
  mLifetime.tick(dt, *this);

  removeDead();
  mTickNumber += 1;
  updateHash();
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
  mLifetime.serialize(i.mutable_lifetime());
  i.set_next_eid(m_idgen.getNext());
  i.set_tick_number(mTickNumber);
  return i;
}

void World::setInitialState(const InitialState& i) {
  mGrid.deserialize(i);
  mClient.deserialize(i.client_data());
  mInventory.deserialize(i.inventories());
  mPhysicsHandler.deserialize(i.physics_data());
  mLifetime.deserialize(i.lifetime());
  m_idgen.setNext(i.next_eid());
  mTickNumber = i.tick_number();
  mInit = true;
  updateHash();
}
