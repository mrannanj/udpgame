#pragma once

#include "common/world/entity_id.h"

const int PLAYER_MODE = 0;
const int OBSERVER_MODE = 1;

struct ClientData {
  int client;
  int mode;
  bool connected;

  EntityId id;
  bool dead;
};
