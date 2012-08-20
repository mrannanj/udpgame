#include "common/world/components/physics.h"

void PhysicsC::update_bbs()
{
  bb_max = position + dimensions;
  bb_min = position - dimensions;
}

void PhysicsC::update_next_bbs()
{
  next_bb_max = next_position + dimensions;
  next_bb_min = next_position - dimensions;
}

