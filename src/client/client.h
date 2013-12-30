#pragma once

#include "common/util/tick_timer.h"

class Client {
public:
  Client(unsigned);
  void run();

private:
  TickTimer m_tick_timer;
};
