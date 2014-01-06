#pragma once

#include <map>
#include <set>
#include <vector>

#include "common/world/components/inputc.h"
#include "common/world/components/physics_handler.h"
#include "common/world/components/input_handler.h"
#include "common/world/components/grid_handler.h"
#include "common/world/components/inventory_handler.h"
#include "common/world/id_generator.h"
#include "common/proto/udpgame.pb.h"

const glm::vec3 spawn_position(5.0f, 8.0f, 5.0f);

class World {
public:
  World();

  int tick(float, const std::vector<InputC>&);
  void spawn_player(int);
  void spawn_monster();

  WorldState getState();
  void setState(const WorldState&);
  void removeDead();
  void defaultWorld();

  bool mInit;
  unsigned mTickNumber;
  std::map<int, EntityId> mClient2Entity;

  PhysicsHandler& physics();
  GridHandler& grid();
  InventoryHandler& inventory();

  std::set<EntityId> mDeleteList;

private:
  IdGenerator m_idgen;
  InputHandler mInputHandler;
  PhysicsHandler mPhysicsHandler;
  InventoryHandler mInventory;
  GridHandler mGrid;
};
