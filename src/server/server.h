#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <arpa/inet.h>

#include "common/util/tick_timer.h"
#include "common/net/udp_socket.h"

class Server
{
public:
  Server(uint16_t, unsigned, int&);
  void listen();

private:
  TickTimer m_tick_timer;
  UDPSocket m_udp_socket;
  int& m_quit;
};

#endif

