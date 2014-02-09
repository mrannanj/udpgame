#include "common/world/components/grid_array.h"

#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

GridArray::GridArray():
  mData(),
  mSize(GRID_SIZE_X * GRID_SIZE_Y * GRID_SIZE_Z)
{
  mData = new char[mSize];
  memset(mData, 0, mSize);
}

GridArray::~GridArray() {
  delete[] mData;
}

size_t GridArray::i(int x, int y, int z) const {
  return x * GRID_SIZE_Y * GRID_SIZE_Z + y * GRID_SIZE_Z + z;
}

char GridArray::heightToBlock(int z) const {
  if (z < 1) return 5;
  if (z < 35) return 4;
  if (z < 45) return 3;
  if (z < 65) return 2;
  return 1;
}

void GridArray::makeFloor() {
  for (unsigned x = 0; x < GRID_SIZE_X; ++x) {
    for (unsigned z = 0; z < GRID_SIZE_Z; ++z) {
      mData[i(x,0,z)] = 3;
      unsigned max_y = min(GRID_SIZE_Z-1, heightFunction(x,z));
      for (unsigned y = 0; y < max_y; ++ y) {
        mData[i(x,y,z)] = heightToBlock(y);
      }
    }
  }
}

unsigned GridArray::heightFunction(int x, int z) const {
  float fx = -1.0f + 2.0f*(x/(float)GRID_SIZE_X);
  float fz = -1.0f + 2.0f*(z/(float)GRID_SIZE_Z);
  return (unsigned)(90.0f * (sin(fx) + cos(fz) + 2.0f)/4);
}

bool GridArray::outsideGrid(int x, int y, int z) const {
  return x < 0 || y < 0 || z < 0 ||
      x >= (int)GRID_SIZE_X || y >= (int)GRID_SIZE_Y || z >= (int)GRID_SIZE_Z;
}

char& GridArray::getRef(int x, int y, int z) {
  return mData[i(x,y,z)];
}

char GridArray::get(int x, int y, int z) const {
  if (outsideGrid(x,y,z)) return 0;
  return mData[i(x,y,z)];
}

void GridArray::set(int x, int y, int z, char value) {
  if (outsideGrid(x,y,z)) return;
  mData[i(x,y,z)] = value;
}

size_t GridArray::size() const {
  return mSize;
}
