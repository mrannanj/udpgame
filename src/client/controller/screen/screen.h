#pragma once

#include "client/view/renderer.h"
#include "client/controller/input/input_manager.h"

struct GameSession;

class Screen {
public:
  virtual ~Screen() {};
  virtual void Activate() = 0;
  virtual void Update(GameSession&, Input&) = 0;
  virtual void Draw(GameSession&, const Renderer&) = 0;
  virtual bool redraw(GameSession&) = 0;
};
