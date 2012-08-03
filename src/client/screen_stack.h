#ifndef CLIENT_SCREEN_STACK_H
#define CLIENT_SCREEN_STACK_H

#include "client/screen.h"

#include <vector>

class ScreenStack {
public:
  ScreenStack();
  void PushScreen(Screen*);
  bool Update(InputReader*, Real);
  void Draw(const Renderer&);
private:
  std::vector<Screen*> screen_stack_;
  unsigned top_;
  unsigned active_;
};

#endif
