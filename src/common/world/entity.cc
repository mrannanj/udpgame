#include "common/world/entity.h"

Entity::Entity():
  x_(0.0f),
  y_(0.0f),
  dir_(0.0f)
{
}

void Entity::Tick(Real /* dt */) {
#if 0
  if (actions_.commands & Action::MOVE_FORWARD)
    y_ += SPEED;
  if (actions_.commands & Action::MOVE_BACK)
    y_ -= SPEED;
  if (actions_.commands & Action::MOVE_LEFT)
    x_ -= SPEED;
  if (actions_.commands & Action::MOVE_RIGHT)
    x_ += SPEED;
#endif
}

