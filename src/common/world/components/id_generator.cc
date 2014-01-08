#include "common/world/components/id_generator.h"

IdGenerator::IdGenerator():
  mNext(1)
{
}

EntityId IdGenerator::generateId() {
  return mNext++;
}

void IdGenerator::setNext(EntityId next) {
  mNext = next;
}

EntityId IdGenerator::getNext() {
  return mNext;
}
