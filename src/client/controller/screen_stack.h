#ifndef CLIENT_CONTROLLER_SCREEN_STACK_H
#define CLIENT_CONTROLLER_SCREEN_STACK_H

#include "client/controller/screen.h"

#include <vector>

class ScreenStack
{
public:
  ScreenStack();

  void push(Screen*);
  bool empty() const;
  Screen* back();
  void pop();
  void clear();
  bool check_dirty();

private:
  std::vector<Screen*> m_screen_stack;
  bool m_dirty;
};

extern ScreenStack g_screen_stack;

#endif
