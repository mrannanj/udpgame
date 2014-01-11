#pragma once

#include <glm/glm.hpp>

struct AABB {
  AABB();
  AABB(int, int, int);
  AABB(const glm::vec3&, const glm::vec3&);

  glm::vec3 min;
  glm::vec3 max;
};
