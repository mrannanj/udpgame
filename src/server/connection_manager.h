#pragma once

#include <vector>

#include "common/net/udp_socket.h"
#include "common/net/connection.h"
#include "common/util/timespec.h"
#include "server/datagram.h"

class ConnectionManager
{
public:
  ConnectionManager();
  void tick(unsigned long);

private:
  void ping(unsigned long);
  void update_timestamp(Connection*, const Datagram&);
  void handle_received_datagrams();
  void handle_datagram(const Datagram&);
  void add_connection(const Datagram&);
  Connection* find_connection(const Datagram&);

  UDPSocket m_udp_socket;
  timespec m_disc_time;
  timespec m_ping_time;
  std::vector<Connection> m_connections;
};

