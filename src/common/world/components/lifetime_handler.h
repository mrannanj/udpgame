#pragma once

#include "common/world/components/world_handler.h"
#include "common/proto/udpgame.pb.h"

class LifetimeHandler : public WorldHandler<Lifetime> {
public:
  void tick(float, World& w);
  void serialize(google::protobuf::RepeatedPtrField<Lifetime>*);
  void deserialize(const google::protobuf::RepeatedPtrField<Lifetime>&);
};
