#pragma once

#include <map>
#include <set>
#include "common/world/components/physics_system.h"
#include "common/world/id_generator.h"
#include "common/proto/udpgame.pb.h"

class World {
public:
  World();

  void tick(float, const ClientInput&, int);
  EntityId spawn_entity(int);
  WorldState getState();
  void setInput(const ClientInput&, int);
  void setState(const WorldState&);
  void handleAMessage(const AMessage&, int);
  void removeDead();
  void defaultWorld();

  std::map<int, EntityId> mClient2Entity;
private:
  IdGenerator m_idgen;
  std::set<EntityId> mDeleteList;
};
