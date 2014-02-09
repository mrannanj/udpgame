#include <iostream>

#include "client/view/text_field.h"
#include "client/view/button.h"
#include "client/controller/input/input.h"
#include "client/view/renderer.h"
#include "client/view/color.h"

TextField::TextField(float left_x, float top_y, float right_x, float font_size, const std::string& text):
  m_left_x(left_x),
  m_top_y(top_y),
  m_right_x(right_x),
  m_bot_y(top_y - font_size),
  m_font_size(font_size),
  m_text_length((unsigned)((right_x-left_x)/font_size)),
  m_text(text),
  m_bg_color(Blue)
{
  assert(m_left_x < m_right_x);
  assert(m_bot_y < m_top_y);
  assert(m_font_size > 0.0f);
}

bool TextField::Update(Input& i)
{
  if (!MouseOver(i.gl_mouse_x, i.gl_mouse_y))
    return false;
  int ci = i.keydown_symbol;
  if (ci > 0)
  {
    char c = (char)ci;
    if (c == '\b' && m_text.size() > 0)
      m_text.resize(m_text.size() - 1);
    else if (m_text.size() < m_text_length && c >= ' ' && c <= 'z')
      m_text += c;
  }

  return true;
}

const std::string& TextField::text() const
{
  return m_text;
}

void TextField::Draw(const Renderer& r) const
{
  r.quad_renderer.On();
  set_color(r.quad_renderer.color_uni(), m_bg_color, 0.5f);
  float q[] = {
    m_left_x, m_bot_y,
    m_right_x, m_top_y,
    m_left_x, m_top_y,
    m_right_x, m_bot_y
  };
  r.quad_renderer.draw_quad(q);
  r.text_renderer.On();
  r.text_renderer.drawText(m_left_x, m_top_y, m_font_size, m_text.substr(0, (size_t)m_text_length), m_bg_color);
}

bool TextField::MouseOver(float x, float y)
{
  return (x >= m_left_x) && (x <= m_right_x)
    && (y <= m_top_y) && (y >= m_bot_y);
}

