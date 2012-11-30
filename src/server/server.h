#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "common/util/tick_timer.h"

class Server
{
public:
  Server(int, int&);
  void listen();

private:
  TickTimer m_tick_timer;
  int m_port;
  int& m_quit;
};

#endif

