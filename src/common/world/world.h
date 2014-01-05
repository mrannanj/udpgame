#pragma once

#include <map>
#include <set>
#include <vector>

#include "common/world/components/inputc.h"
#include "common/world/components/physics_handler.h"
#include "common/world/components/input_handler.h"
#include "common/world/components/grid_handler.h"
#include "common/world/id_generator.h"
#include "common/proto/udpgame.pb.h"

class World {
public:
  World();

  int tick(float, const std::vector<InputC>&);
  EntityId spawn_entity(int);
  WorldState getState();
  void setState(const WorldState&);
  void removeDead();
  void defaultWorld();

  bool mInit;
  unsigned mTickNumber;
  std::map<int, EntityId> mClient2Entity;

  PhysicsHandler& physics();
  GridHandler& grid();

  std::set<EntityId> mDeleteList;

private:
  IdGenerator m_idgen;
  InputHandler mInputHandler;
  PhysicsHandler mPhysicsHandler;
  GridHandler mGrid;
};
