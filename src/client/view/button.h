#ifndef CLIENT_VIEW_BUTTON_H
#define CLIENT_VIEW_BUTTON_H

#include <string>

struct Color;
struct Input;
class Renderer;

class Button {
public:
  Button(float, float, float, const std::string&);

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

#endif
