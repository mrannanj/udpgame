#include "client/view/window.h"

float gl_pos_x(int x) {
  return ((float)x / (WINDOW_WIDTH/2)) - 1.0f;
}

float gl_pos_y(int y) {
  return 1.0f - (float)y / (WINDOW_HEIGHT/2);
}

