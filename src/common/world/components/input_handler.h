#pragma once

#include "common/world/entity_id.h"
#include "common/world/components/world_handler.h"
#include "common/proto/udpgame.pb.h"

#include <vector>

struct InputHandler: public WorldHandler <FrameInput, FrameInput> {
	void tick(float, World&);
	FrameInput *getByClient(int);
};
