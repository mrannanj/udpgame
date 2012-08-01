#ifndef CLIENT_GAME_STATE_H
#define CLIENT_GAME_STATE_H

#include "common/world/real.h"
#include "client/view/renderer.h"
#include "client/input/input_reader.h"

class GameState {
public:
  virtual bool Update(InputReader*, Real) = 0;
  virtual void Draw(const Renderer&) = 0;
};

#endif
