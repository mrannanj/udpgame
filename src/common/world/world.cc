#include "common/config.h"
#include "common/platform.h"
#include "common/world/world.h"
#include "common/world/components/physics.h"
#include "common/world/components/grid_handler.h"

#include <SDL2/SDL.h>
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
	m_idgen()
{
}

void World::spawn_player(int clientid)
{
	EntityId eid = m_idgen.generateId();

	Physics p;
	p.entityid = eid;
	p.half_dim = glm::vec3(0.4f, 0.9f, 0.4f);
	p.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

void World::removeDead()
{
}
