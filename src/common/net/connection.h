#ifndef COMMON_NET_CONNECTION_H
#define COMMON_NET_CONNECTION_H

#include <ctime>
#include <arpa/inet.h>
#include <ostream>

enum class ConnectionState
{
  CONNECTED,
  STALE,
  DISCONNECTED
};

struct Connection
{
  timespec ts;
  ConnectionState state;
  sockaddr_storage sa;
  socklen_t sa_len;
};

#endif

