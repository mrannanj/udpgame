
#include <iostream>

#include "client/view/button.h"
#include "client/controller/input/input.h"
#include "client/view/renderer.h"
#include "client/view/color.h"

Button::Button(float x, float y, float size, const std::string& text):
  x_(x),
  y_(y),
  size_(size),
  text_(text),
  bg_color_(&Green)
{
}

bool Button::Update(Input& i) {
  if (MouseOver(i.gl_mouse_x, i.gl_mouse_y)) {
    bg_color_ = &Blue;
    if (i.consume_mouse_click(Mouse::LEFT)) {
      return true;
    }
  } else {
    bg_color_ = &Green;
  }
  return false;
}

void Button::Draw(const Renderer& r) const {
  r.text_renderer.On();
  r.text_renderer.DrawText(x_, y_, size_, text_, *bg_color_);
}

bool Button::MouseOver(float x, float y) {
  return (x >= x_) && (x <= (x_ + text_.size()*size_))
    && (y <= y_) && (y >= y_ - size_);
}
