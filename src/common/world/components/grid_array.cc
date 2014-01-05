#include "common/world/components/grid_array.h"

#include <cstring>

GridArray::GridArray():
  mData(),
  mSize(GRID_SIZE_X * GRID_SIZE_Y * GRID_SIZE_Z)
{
  memset(mData, 0, mSize);
}

void GridArray::makeFloor() {
  for (unsigned x = 0; x < GRID_SIZE_X; ++x)
    for (unsigned z = 0; z < GRID_SIZE_Z; ++z)
      mData[x][0][z] = 1;
}

bool GridArray::outsideGrid(int x, int y, int z) const {
  return x < 0 or y < 0 or z < 0 or
      x >= GRID_SIZE_X or y >= GRID_SIZE_Y or z >= GRID_SIZE_Z;
}

char& GridArray::getUnsafe(int x, int y, int z) {
  return mData[x][y][z];
}

char GridArray::get(int x, int y, int z) const {
  if (outsideGrid(x,y,z)) return 0;
  return mData[x][y][z];
}

void GridArray::set(int x, int y, int z, char value) {
  if (outsideGrid(x,y,z)) return;
  mData[x][y][z] = value;
}

size_t GridArray::size() const {
  return mSize;
}
