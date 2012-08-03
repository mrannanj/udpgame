#ifndef COMMON_WORLD_ENTITY_H
#define COMMON_WORLD_ENTITY_H

#include "common/world/real.h"

#define SPEED 0.02f

struct Entity {
  Entity();

  // phys comp
  Real x_;
  Real y_;
  Real dir_;

  // input comp
  //Actions actions_;

  // update all
  void Tick(Real);
};

#endif

