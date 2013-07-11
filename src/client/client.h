#pragma once

#include "common/util/tick_timer.h"
#include "client/client_connection.h"

class Client {
public:
  Client(unsigned, int&);
  void run();

private:
  TickTimer m_tick_timer;
  int& m_quit;
  ClientConnection m_client_connection;
};

