#include "common/config.h"
#include "common/platform.h"
#include "common/world/world.h"
#include "common/world/components/physics.h"
#include "common/world/components/grid_handler.h"
#include "common/world/components/light_handler.h"

#include <SDL.h>
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
	mDeleteList(),
	m_idgen(),
	mInputHandler(),
	mPhysicsHandler(),
	mInventory(),
	mClient(),
	mGrid(),
	mLifetime(),
	mAi(),
	mLight(),
	mHealth(),
	mDamage()
{
	if (mInit)
		mGrid.defaultGrid();
	updateHash();
}

const uint32_t *World::hashes() const
{
	return mHashes;
}

void World::updateHash()
{
	mHashes[HANDLER_PHYSICS] = mPhysicsHandler.hash();
	mHashes[HANDLER_CLIENT] = mClient.hash();
	mHashes[HANDLER_INVENTORY] = mInventory.hash();
	mHashes[HANDLER_LIFETIME] = mLifetime.hash();
	mHashes[HANDLER_AI] = mAi.hash();
	mHashes[HANDLER_LIGHT] = mLight.hash();
	mHashes[HANDLER_HEALTH] = mHealth.hash();
	mHashes[HANDLER_DAMAGE] = mDamage.hash();
}

void World::spawn_monster(const Physics& o)
{
	EntityId eid = m_idgen.generateId();

	Physics p;

	p.entityid = eid;
	p.position = o.eye_position() + o.look_direction() * 2.0f;
	p.half_dim = glm::vec3(0.4f, 0.4f, 0.4f);
	p.velocity = o.look_direction() * 10.0f;
	p.type = ObjectType::TORCH;
	mPhysicsHandler.add(p);

	Inventory i;
	i.entityid = eid;
	i.wielding = ObjectType::NONE;
	mInventory.add(i);

	Health h;
	h.set_eid(eid);
	h.set_max_hp(100);
	h.set_cur_hp(100);
	mHealth.add(h);
}

void World::throw_object(const Physics& o, ObjectType t)
{
	EntityId eid = m_idgen.generateId();

	Physics p;

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

	Damage d;
	d.set_eid(eid);
	d.set_damage(30);
	mDamage.add(d);
}

void World::onBlockDestruction(int x, int y, int z)
{
	char& b = mGrid.mArr.getRef(x, y, z);

	EntityId eid = m_idgen.generateId();

	Physics p;

	p.entityid = eid;
	p.position = glm::vec3((float)x, (float)y, (float)z) + 0.5f;
	p.half_dim = glm::vec3(0.2f, 0.2f, 0.2f);
	p.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	p.type = (ObjectType) b;
	mPhysicsHandler.add(p);
	b = 0;

	Lifetime l;
	l.set_eid(eid);
	l.set_ttl(10.0f);
	mLifetime.add(l);
}

void World::spawn_player(int clientid)
{
	EntityId eid = m_idgen.generateId();

	Physics p;

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

	ClientData *cd = mClient.getByClient(clientid);
	assert(cd != nullptr);
	cd->set_dead(0);
	cd->set_eid(eid);
	cd->set_mode(ClientMode::MODE_PLAYER);
}

void World::tick(const FrameInputs& fis)
{
	float dt = secs_per_tick;

	mDeleteList.clear();
	mInputHandler.deserialize(fis.frame_inputs());

	mInputHandler.tick(dt, *this);
	mClient.tick(dt, *this);
	mPhysicsHandler.tick(dt, *this);
	mInventory.tick(dt, *this);
	mLifetime.tick(dt, *this);
	mAi.tick(dt, *this);
	mHealth.tick(dt, *this);
	mDamage.tick(dt, *this);

	removeDead();
	mTickNumber += 1;
	updateHash();
}

void World::removeDead()
{
	mClient.handleDead(mDeleteList);
	mPhysicsHandler.handleDead(mDeleteList);
	mInventory.handleDead(mDeleteList);
	mLifetime.handleDead(mDeleteList);
	mAi.handleDead(mDeleteList);
	mLight.handleDead(mDeleteList);
	mHealth.handleDead(mDeleteList);
	mDamage.handleDead(mDeleteList);
}

InventoryHandler& World::inventory()
{
	return mInventory;
}

PhysicsHandler& World::physics()
{
	return mPhysicsHandler;
}

GridHandler& World::grid()
{
	return mGrid;
}

ClientHandler& World::client()
{
	return mClient;
}

InputHandler& World::input()
{
	return mInputHandler;
}

LightHandler& World::light()
{
	return mLight;
}

HealthHandler& World::health()
{
	return mHealth;
}

DamageHandler& World::damage()
{
	return mDamage;
}

InitialState World::getInitialState()
{
	InitialState i;
	mGrid.serialize(i);
	mClient.serialize(i.mutable_client_data());
	mInventory.serialize(i.mutable_inventories());
	mPhysicsHandler.serialize(i.mutable_physics_data());
	mLifetime.serialize(i.mutable_lifetime());
	mAi.serialize(i.mutable_ai());
	mLight.serialize(i.mutable_light());
	mHealth.serialize(i.mutable_health());
	mDamage.serialize(i.mutable_damage());
	i.set_next_eid(m_idgen.getNext());
	i.set_tick_number(mTickNumber);
	return i;
}

void World::setInitialState(const InitialState& i)
{
	mGrid.deserialize(i);
	mClient.deserialize(i.client_data());
	mInventory.deserialize(i.inventories());
	mPhysicsHandler.deserialize(i.physics_data());
	mLifetime.deserialize(i.lifetime());
	mAi.deserialize(i.ai());
	mLight.deserialize(i.light());
	mHealth.deserialize(i.health());
	mDamage.deserialize(i.damage());
	m_idgen.setNext(i.next_eid());
	mTickNumber = i.tick_number();
	mInit = true;
	updateHash();
}

void
World::serializeHashes(google::protobuf::RepeatedField<uint32_t> *hashes) const
{
	for (int i = 0; i < HANDLER_COUNT; ++i)
		*(hashes->Add()) = mHashes[i];
}
