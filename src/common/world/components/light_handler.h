#pragma once

#include "common/world/components/world_handler.h"
#include "common/proto/udpgame.pb.h"
#include "common/util/hash.h"

class LightHandler: public WorldHandler<Light, Light> {};

template <> uint32_t inline thash<Light> (const Light& l) {
	return thash(l.eid()) ^ thash(l.intensity());
}
