#ifndef CLIENT_VIEW_COLOR_H
#define CLIENT_VIEW_COLOR_H

#include <GL/gl.h>

struct Color {
  Color(float r_, float g_, float b_): r(r_), g(g_), b(b_) {}
  float r;
  float g;
  float b;
};

void set_color(GLint, const Color&, float);

extern Color Red;
extern Color Green;
extern Color Blue;

#endif
