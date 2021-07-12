#include "common/world/components/inventory.h"

Inventory::Inventory():
	entityid(0)
{
}

EntityId Inventory::eid() const
{
	return entityid;
}
