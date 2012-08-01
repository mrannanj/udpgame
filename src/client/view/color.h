#ifndef CLIENT_VIEW_COLOR_H
#define CLIENT_VIEW_COLOR_H

struct Color {
  Color(float r_, float g_, float b_): r(r_), g(g_), b(b_) {}
  float r;
  float g;
  float b;
};

Color Red(1.0f, 0.0f, 0.0f);
Color Green(0.0f, 1.0f, 0.0f);
Color Blue(0.0f, 0.0f, 1.0f);

#endif
