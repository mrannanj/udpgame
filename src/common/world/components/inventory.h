#pragma once

#include "common/proto/udpgame.pb.h"
#include "common/world/entity_id.h"

#include <map>

struct Inventory {
  Inventory();
  Inventory(const InventoryData&);
  operator InventoryData() const;

  EntityId eid() const;

  EntityId entityid;
  ObjectType wielding;
  std::map<ObjectType, int32_t> itemCount;
};
