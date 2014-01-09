#include "common/world/components/grid_array.h"

#include <cstring>

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

void GridArray::makeFloor() {
  memset(mData, 1, mSize);
  for (unsigned x = 0; x < GRID_SIZE_X; ++x) {
    for (unsigned z = 0; z < GRID_SIZE_Z; ++z) {
      mData[i(x,0,z)] = 3;
    }
  }
}

bool GridArray::outsideGrid(int x, int y, int z) const {
  return x < 0 or y < 0 or z < 0 or
      x >= GRID_SIZE_X or y >= GRID_SIZE_Y or z >= GRID_SIZE_Z;
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
