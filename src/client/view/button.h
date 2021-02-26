#pragma once

#include <string>
#include "client/view/hitbox_2d.h"

struct Color;
struct Input;
class Renderer;

class Button {
public:
  Button(float, float, float, const std::string&);
  Button(const Button&) = delete;
  Button& operator=(const Button&) = delete;

  bool Update(Input&);
  void Draw(const Renderer&);

private:
  bool MouseOver(float, float);

  float x_;
  float y_;
  float size_;
  Hitbox2D hitbox_;
  std::string text_;
  Color* bg_color_;
};
