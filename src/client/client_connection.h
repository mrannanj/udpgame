#ifndef CLIENT_CLIENT_CONNECTION_H
#define CLIENT_CLIENT_CONNECTION_H

#include "common/net/udp_socket.h"

class ClientConnection
{
public:
  ClientConnection();
  void initiate_connection();
  void tick();

private:
  UDPSocket m_udp_socket;
  sockaddr_in m_sa_server;
};

#endif

