#pragma once

#include <string>

struct Color;
struct Input;
class Renderer;

class Button {
public:
  Button(float, float, float, const std::string&);
  Button(const Button&) = delete;
  Button& operator=(const Button&) = delete;

  bool Update(Input&);
  void Draw(const Renderer&) const;

private:
  bool MouseOver(float, float);

  float x_;
  float y_;
  float size_;
  std::string text_;
  Color* bg_color_;
};
