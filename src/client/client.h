#pragma once

#include "common/util/tick_timer.h"

class Client {
public:
  Client(unsigned, volatile int&);
  void run();

private:
  TickTimer m_tick_timer;
  volatile int& m_quit;
};
