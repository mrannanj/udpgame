#pragma once

constexpr int GRID_SIZE_X = 10;
constexpr int GRID_SIZE_Y = 10;
constexpr int GRID_SIZE_Z = 10;

struct GridArray {
  GridArray();

  void makeFloor();
  char get(int, int, int) const;
  void set(int, int, int, char);
  bool outsideGrid(int, int, int) const;

  char mData[GRID_SIZE_X][GRID_SIZE_Y][GRID_SIZE_Z];
};
