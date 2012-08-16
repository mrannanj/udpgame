
#include <SDL.h>
#include <GL/glew.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "common/world/world.h"

World::World() {
  memset(m_blocks, 0, WORLD_MAX_X*WORLD_MAX_Y*WORLD_MAX_Z);
  for (unsigned x = 0; x < WORLD_MAX_X; ++x)
    for (unsigned z = 0; z < WORLD_MAX_Z; ++z)
      m_blocks[x][0][z] = (char)(x ^ z);
}

unsigned World::block_index(unsigned x, unsigned y, unsigned z) {
  assert(x < WORLD_MAX_X);
  assert(y < WORLD_MAX_Y);
  assert(z < WORLD_MAX_Z);
  return (x * WORLD_MAX_Y * WORLD_MAX_Z) + (y * WORLD_MAX_Z) + z;
}

char World::block(unsigned x, unsigned y, unsigned z) {
  return m_blocks[x][y][z];
}
