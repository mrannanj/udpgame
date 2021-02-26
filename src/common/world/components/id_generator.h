#pragma once

#include "common/world/entity_id.h"

class IdGenerator {
public:
	IdGenerator();
	EntityId generateId();

	void setNext(EntityId);
	EntityId getNext();

private:
	 EntityId mNext;
};
