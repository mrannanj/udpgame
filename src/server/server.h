#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "common/util/tick_timer.h"

class Server
{
public:
  Server(int, unsigned, int&);
  void listen();

private:
  unsigned long m_ns_per_tick;
  TickTimer m_tick_timer;
  int m_port;
  int& m_quit;
};

#endif

