#ifndef CLIENT_CONTROLLER_SCREEN_H
#define CLIENT_CONTROLLER_SCREEN_H

#include "client/view/renderer.h"
#include "client/controller/input/input_manager.h"

class Screen {
public:
  virtual void Activate() = 0;
  virtual void Update(InputManager&, float) = 0;
  virtual void Draw(const Renderer&) = 0;
};

#endif
