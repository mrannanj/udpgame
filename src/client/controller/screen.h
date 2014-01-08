#pragma once

#include "client/view/renderer.h"
#include "client/controller/input/input_manager.h"

struct GameSession;

class Screen {
public:
  virtual void Activate() = 0;
  virtual void Update(GameSession&, InputManager&, float) = 0;
  virtual void Draw(GameSession&, const Renderer&) = 0;
  virtual bool redraw() = 0;
};
