#ifndef CLIENT_SCREEN_H
#define CLIENT_SCREEN_H

#include "common/world/real.h"
#include "client/view/renderer.h"
#include "client/input/input_reader.h"

class Screen {
public:
  virtual bool Update(InputReader*, Real) = 0;
  virtual void Draw(const Renderer&) = 0;
};

#endif
