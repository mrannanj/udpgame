#ifndef COMMON_NET_CONNECTION_H
#define COMMON_NET_CONNECTION_H

#include <ctime>
#include <arpa/inet.h>

enum class ConnectionState
{
  INACTIVE,
  CONNECTED,
  STALE
};

class Connection
{
public:
  Connection(const sockaddr_in&, const timespec&);

private:
  ConnectionState m_state;
  sockaddr_in m_sockaddr;
  timespec m_last_received_time;
};

#endif

