#pragma once

#include <ostream>

#include "common/world/entity_id.h"
#include "common/proto/udpgame.pb.h"
#include "client/controller/input/input.h"

struct InputC {
  InputC();
  InputC(const Input&);
  InputC(const ClientInput&);

  EntityId id;
  unsigned actions;
  float horizontal_angle_delta;
  float vertical_angle_delta;
};

std::ostream& operator<<(std::ostream&, const InputC&);

