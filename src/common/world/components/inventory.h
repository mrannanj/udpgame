#pragma once

#include "common/world/entity_id.h"
#include "common/util/hash.h"

#include <map>

struct Inventory {
	Inventory();

	EntityId eid() const;

	EntityId entityid;
};

template <> uint32_t inline thash<Inventory> (const Inventory& i) {
	uint32_t h = thash(i.entityid);
	return h;
}
