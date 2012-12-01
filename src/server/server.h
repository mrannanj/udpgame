#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <arpa/inet.h>

#include "common/util/tick_timer.h"
#include "server/connection_manager.h"

class Server
{
public:
  Server(unsigned, int&);
  void listen();

private:
  TickTimer m_tick_timer;
  ConnectionManager m_connection_manager;
  int& m_quit;
};

#endif

