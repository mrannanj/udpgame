#pragma once

#include "common/world/components/world_handler.h"
#include "common/proto/udpgame.pb.h"

class ClientHandler : public WorldHandler<ClientData> {
public:
  void tick(float, World&);
  void handleDead(const std::set<EntityId>&);
  void markDead(EntityId);
  void remove(EntityId);
  ClientData* getByClient(int);
  void removeByClient(int);
  void serialize(google::protobuf::RepeatedPtrField<ClientData>*);
  void deserialize(const google::protobuf::RepeatedPtrField<ClientData>&);
};

