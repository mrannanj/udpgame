#pragma once

#include "common/world/components/world_handler.h"
#include "common/world/components/inventory.h"
#include "common/proto/udpgame.pb.h"

class InventoryHandler : public WorldHandler<Inventory> {
public:
  void tick(float, World&);
  void serialize(google::protobuf::RepeatedPtrField<InventoryData>*);
  void deserialize(const google::protobuf::RepeatedPtrField<InventoryData>&);

private:
  void pickupItems(World&);
};
