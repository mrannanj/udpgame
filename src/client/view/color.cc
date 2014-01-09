#include <GL/glew.h>

#include "client/view/color.h"

Color Red(1.0f, 0.0f, 0.0f);
Color Green(0.0f, 1.0f, 0.0f);
Color Blue(0.0f, 0.0f, 1.0f);

void set_color(GLint uniform, const Color& c, float alpha) {
  glUniform4f(uniform, c.r, c.g, c.b, alpha);
}

