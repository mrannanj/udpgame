#pragma once

#include <map>
#include <set>
#include <vector>

#include "common/world/components/id_generator.h"

class World {
public:
	World(bool);

	void spawn_player(int);
	void onBlockDestruction(int, int, int);

	void removeDead();

	const uint32_t *hashes() const;

	bool mInit;
	unsigned mTickNumber;

	std::set<EntityId> mDeleteList;

private:
	void updateHash();

	IdGenerator m_idgen;
};
