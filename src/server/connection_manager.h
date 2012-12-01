#ifndef SERVER_CONNECTION_MANAGER_H
#define SERVER_CONNECTION_MANAGER_H

#include <vector>

#include "common/net/udp_socket.h"
#include "common/net/connection.h"
#include "server/datagram.h"

class ConnectionManager
{
public:
  ConnectionManager();
  void tick();
  void handle_datagram(const Datagram&) const;

private:
  UDPSocket m_udp_socket;
  std::vector<Connection> m_connections;
};

#endif

