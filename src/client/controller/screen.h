#ifndef CLIENT_CONTROLLER_SCREEN_H
#define CLIENT_CONTROLLER_SCREEN_H

#include "common/world/real.h"
#include "client/view/renderer.h"
#include "client/controller/input/input_reader.h"

class Screen {
public:
  virtual void Update(InputReader&, Real) = 0;
  virtual void Draw(const Renderer&) = 0;
};

#endif
