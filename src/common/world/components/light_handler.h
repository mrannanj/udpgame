#pragma once

#include "common/world/components/world_handler.h"
#include "common/proto/udpgame.pb.h"

class LightHandler : public WorldHandler<Light, Light> {};
