
#include <iostream>

#include "client/view/button.h"
#include "client/controller/input/input.h"
#include "client/view/renderer.h"
#include "client/view/color.h"

Button::Button(float x, float y, float size, const std::string& text):
	x_(x),
	y_(y),
	size_(size),
	hitbox_(),
	text_(text),
	bg_color_(&Green)
{
}

bool Button::Update(Input& i)
{
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

void Button::Draw(const Renderer& r)
{
	r.ft_renderer.On();
	hitbox_ = r.ft_renderer.DrawText(x_, y_, size_, text_, *bg_color_);
}

bool Button::MouseOver(float x, float y)
{
	return hitbox_.mouseOver(x, y);
}
