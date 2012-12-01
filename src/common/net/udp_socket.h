#ifndef COMMON_NET_UDP_SOCKET_H
#define COMMON_NET_UDP_SOCKET_H

#include <arpa/inet.h>

class UDPSocket
{
public:
  UDPSocket(uint16_t);
  ~UDPSocket();
  int fd() const;

private:
  void set_nonblocking();

  uint16_t m_port;
  int m_fd;
  sockaddr_in m_sa_me;
};

#endif

