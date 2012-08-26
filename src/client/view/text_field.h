#ifndef CLIENT_VIEW_TEXT_FIELD_H
#define CLIENT_VIEW_TEXT_FIELD_H

#include <string>

struct Color;
struct Input;
class Renderer;

class TextField {
public:
  TextField(float, float, float, float, const std::string&);

  bool Update(Input&);
  void Draw(const Renderer&) const;
  const std::string& text() const;

private:
  bool MouseOver(float, float);

  float m_left_x;
  float m_top_y;
  float m_right_x;
  float m_bot_y;
  float m_font_size;
  unsigned m_text_length;
  std::string m_text;
  Color& m_fg_color;
  Color& m_bg_color;
};




#endif
