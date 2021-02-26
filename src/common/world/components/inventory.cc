#include "common/world/components/inventory.h"

Inventory::Inventory():
	entityid(0),
	wielding(ObjectType::NONE),
	itemCount()
{
}

Inventory::Inventory(const InventoryData& id):
	entityid(id.eid()),
	wielding(id.wielding()),
	itemCount()
{
	for (int i = 0; i < id.count_size(); ++i) {
		const ObjectCount& oc = id.count(i);
		itemCount.insert({oc.type(), oc.count()});
	}
}

Inventory::operator InventoryData()const
{
	InventoryData id;
	id.set_eid(entityid);
	id.set_wielding(wielding);
	for (const auto& p : itemCount) {
		ObjectCount * oc = id.add_count();
		oc->set_type(p.first);
		oc->set_count(p.second);
	}
	return id;
}

EntityId Inventory::eid() const
{
	return entityid;
}
