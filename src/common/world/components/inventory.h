#pragma once

#include "common/proto/udpgame.pb.h"
#include "common/world/entity_id.h"
#include "common/util/hash.h"

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

template<>
uint32_t inline thash<Inventory>(const Inventory& i) {
  uint32_t h = thash(i.entityid) ^ thash(i.wielding);
  for (const auto& ic : i.itemCount) {
    h ^= thash(ic.first) ^ thash(ic.second);
  }
  return h;
}
