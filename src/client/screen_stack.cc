#include "client/screen_stack.h"

ScreenStack::ScreenStack():
  top_(0),
  active_(0)
{

}

void ScreenStack::PushScreen(Screen* screen) {
  screen_stack_.push_back(screen);
  top_ += 1;
  active_ += 1;
}

bool ScreenStack::Update(InputReader* input, Real dt) {
  if (top_ == 0)
    return true;
  for (unsigned i = active_ - 1; i < top_ - 1; ++i) {
    screen_stack_[i]->Update(nullptr, dt);
  }
  return screen_stack_[top_ - 1]->Update(input, dt);
}

void ScreenStack::Draw(const Renderer& r) {
  for (unsigned i = active_ - 1; i < top_ ; ++i) {
    screen_stack_[i]->Draw(r);
  }
}
