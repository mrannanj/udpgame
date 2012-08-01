#ifndef CLIENT_STATE_STACK_H
#define CLIENT_STATE_STACK_H

#include "client/game_state.h"

#include <vector>

class StateStack {
public:
  StateStack();
  void PushState(GameState*);
  bool Update(InputReader*, Real);
  void Draw(const Renderer&);
private:
  std::vector<GameState*> state_stack_;
  unsigned top_;
  unsigned active_;
};

#endif
