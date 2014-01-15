#pragma once

#include <map>
#include <set>
#include <vector>

#include "common/world/components/physics_handler.h"
#include "common/world/components/input_handler.h"
#include "common/world/components/grid_handler.h"
#include "common/world/components/inventory_handler.h"
#include "common/world/components/client_handler.h"
#include "common/world/components/lifetime_handler.h"
#include "common/world/components/ai_handler.h"
#include "common/world/components/id_generator.h"
#include "common/world/components/light_handler.h"
#include "common/proto/udpgame.pb.h"

class World {
public:
  World(bool);

  void tick(const FrameInputs&);
  void spawn_player(int);
  void throw_object(const Physics&, ObjectType);
  void onBlockDestruction(int, int, int);
  void throw_torch(const Physics&);

  void removeDead();

  InitialState getInitialState();
  void setInitialState(const InitialState&);

  void serializeHashes(google::protobuf::RepeatedField<uint32_t>*) const;
  const uint32_t* hashes() const;

  bool mInit;
  unsigned mTickNumber;

  InputHandler& input();
  PhysicsHandler& physics();
  GridHandler& grid();
  InventoryHandler& inventory();
  ClientHandler& client();
  LightHandler& light();

  std::set<EntityId> mDeleteList;

private:
  void updateHash();

  IdGenerator m_idgen;
  InputHandler mInputHandler;
  PhysicsHandler mPhysicsHandler;
  InventoryHandler mInventory;
  ClientHandler mClient;
  GridHandler mGrid;
  LifetimeHandler mLifetime;
  AiHandler mAi;
  LightHandler mLight;

  uint32_t mHashes[Handler::HANDLER_COUNT];
};
