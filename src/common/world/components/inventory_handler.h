#pragma once

#include "common/world/components/world_handler.h"
#include "common/proto/udpgame.pb.h"

struct InventoryHandler : public WorldHandler<Inventory> {
  void tick(float, World&);
  void serialize(google::protobuf::RepeatedPtrField<Inventory>*);
  void deserialize(const google::protobuf::RepeatedPtrField<Inventory>&);
};
