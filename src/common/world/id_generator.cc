#include "common/world/id_generator.h"

IdGenerator::IdGenerator():
  next_id_(1)
{
}

EntityId IdGenerator::NextId() {
  return next_id_++;
}

