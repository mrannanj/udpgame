#pragma once

#include "common/util/hash.h"

#include "common/include/glm.h"

struct AABB {
  AABB();
  AABB(int, int, int);
  AABB(const glm::vec3&, const glm::vec3&);

  glm::vec3 min;
  glm::vec3 max;
};

template<>
uint32_t inline thash<AABB>(const AABB& p) {
  return thash(p.min) ^ thash(p.max);
}
