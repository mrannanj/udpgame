#ifndef COMMON_WORLD_WORLD_H
#define COMMON_WORLD_WORLD_H

#include <map>
#include "common/google.h"

#define WORLD_MAX_X 25
#define WORLD_MAX_Y 25
#define WORLD_MAX_Z 25

class World {
public:
  World();
  DISALLOW_COPY_AND_ASSIGN(World);

  const char* blocks() const;
  unsigned block_index(unsigned x, unsigned y, unsigned z);
  char block(unsigned x, unsigned y, unsigned z);

private:
  char m_blocks[WORLD_MAX_X][WORLD_MAX_Y][WORLD_MAX_Z];
};

#endif

