#include <algorithm>

#include "common/world/components/collision.h"

bool AABBvsAABB(const AABB& a, const AABB& b) {
  if (a.max[0] < b.min[0] || a.min[0] > b.min[0]) return false;
  if (a.max[1] < b.min[1] || a.min[1] > b.min[1]) return false;
  if (a.max[2] < b.min[2] || a.min[2] > b.min[2]) return false;
  return true;
}

float AABBvsAABB_overlap(const AABB& a, const AABB& b, unsigned& axis) {
  axis = 4;
  float smallest_overlap = FLT_MAX;
  float smallest_overlap_abs = FLT_MAX;
  for (unsigned i = 0; i < 3; ++i) {
    float overlap = a.max[i] - b.min[i];
    float overlap_abs = fabsf(overlap);
    if (overlap_abs > 0.0f && smallest_overlap_abs > overlap_abs) {
      smallest_overlap = overlap;
      smallest_overlap_abs = overlap_abs;
      axis = i;
    }

    overlap = a.min[i] - b.max[i];
    overlap_abs = fabsf(overlap);
    if (overlap_abs > 0.0f && smallest_overlap_abs > overlap_abs) {
      smallest_overlap = overlap;
      smallest_overlap_abs = overlap_abs;
      axis = i;
    }
  }
  assert(axis != 4);
  return smallest_overlap;
}

bool AABBvsRay(const AABB& a, const glm::vec3& p, const glm::vec3& d,
    float& tmin, int& axis, int& dir)
{
  tmin = 0.0f;
  float tmax = FLT_MAX;
  axis = 4;
  for (int i = 0; i < 3; i++) {
    int swapped = 1;
    if (fabsf(d[i]) < FLT_MIN) {
      if (p[i] < a.min[i] || p[i] > a.max[i]) {
        return false;
      }
    } else {
      float div = 1.0f/d[i];
      float t1 = (a.min[i] - p[i]) * div;
      float t2 = (a.max[i] - p[i]) * div;

      if (t1 > t2) {
        swapped = -1;
        std::swap(t1, t2);
      }
      if (t1 > tmin) {
        tmin = t1;
        axis = i;
        dir = -1 * swapped;
      }
      if (tmax > t2) {
        tmax = t2;
      }
      if (tmin > tmax) {
        return false;
      }
    }
  }
  return axis != 4; // axis 4 up to no good
}
