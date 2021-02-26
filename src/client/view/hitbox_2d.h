#pragma once

struct Hitbox2D {
  float left = 0.0f;
  float right = 0.0f;
  float bot = 0.0f;
  float top = 0.0f;

  bool mouseOver(float, float);
};
