#pragma once

#include "common/world/components/world_handler.h"
#include "common/proto/udpgame.pb.h"

class HealthHandler: public WorldHandler<Health, Health> {
public:
	void tick(float, World&);
};

template <> uint32_t inline thash<Health> (const Health& h) {
	return thash(h.eid()) ^ thash(h.cur_hp()) ^ thash(h.max_hp());
}
