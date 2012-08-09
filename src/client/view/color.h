#ifndef CLIENT_VIEW_COLOR_H
#define CLIENT_VIEW_COLOR_H

struct Color {
  Color(float r_, float g_, float b_): r(r_), g(g_), b(b_) {}
  float r;
  float g;
  float b;
};

extern Color Red;
extern Color Green;
extern Color Blue;

#endif
