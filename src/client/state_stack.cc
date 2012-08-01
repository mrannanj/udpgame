#include "client/state_stack.h"

StateStack::StateStack():
  top_(0),
  active_(0)
{

}

void StateStack::PushState(GameState* state) {
  state_stack_.push_back(state);
  top_ += 1;
  active_ += 1;
}

bool StateStack::Update(InputReader* input, Real dt) {
  if (top_ == 0)
    return true;
  for (unsigned i = active_ - 1; i < top_ - 1; ++i) {
    state_stack_[i]->Update(nullptr, dt);
  }
  return state_stack_[top_ - 1]->Update(input, dt);
}

void StateStack::Draw(const Renderer& r) {
  for (unsigned i = active_ - 1; i < top_ ; ++i) {
    state_stack_[i]->Draw(r);
  }
}
