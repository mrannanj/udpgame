#pragma once

#include <cstddef>

const unsigned GRID_SIZE_X = 90;
const unsigned GRID_SIZE_Y = 90;
const unsigned GRID_SIZE_Z = 90;
const unsigned GRID_SIZE[] = {GRID_SIZE_X, GRID_SIZE_Y, GRID_SIZE_Z};

struct GridArray {
  GridArray();
  ~GridArray();

  GridArray(const GridArray&) = delete;
  GridArray& operator=(const GridArray&) = delete;

  unsigned heightFunction(int, int) const;
  char heightToBlock(int) const;
  void makeFloor();
  char get(int, int, int) const;
  bool outsideGrid(int, int, int) const;
  char& getRef(int x, int y, int z);
  void set(int, int, int, char);
  size_t size() const;

  size_t i(int x, int y, int z) const;

  char* mData;

private:
  size_t mSize;
};
