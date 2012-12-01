#ifndef SERVER_DATAGRAM_H
#define SERVER_DATAGRAM_H

#include <ostream>
#include <arpa/inet.h>

struct Datagram
{
  sockaddr_storage* sa;
  socklen_t sa_len;
  char* buf;
  size_t len;
  timespec *ts;
};

std::ostream& operator<<(std::ostream&, const Datagram&);

#endif

