#include <iostream>
#include <cassert>
#include <sys/ioctl.h>

#include "server/connection_manager.h"
#include "common/net/udp_socket.h"
#include "common/config.h"

#define BUF_SIZE 512

ConnectionManager::ConnectionManager():
  m_udp_socket(SERVER_PORT)
{
}

void ConnectionManager::handle_datagram(const Datagram& d) const
{
  std::cout << d << std::endl;
}

void ConnectionManager::tick()
{
  int fd = m_udp_socket.fd();
  ssize_t nread = 0;
  char buf[BUF_SIZE];
  sockaddr_storage sa;
  socklen_t sa_len = sizeof(sockaddr_storage);
  timespec ts;
  Datagram d{&sa, sa_len, buf, 0, &ts};

  for (;;)
  {
    nread = recvfrom(fd, buf, BUF_SIZE, 0,
      (sockaddr*)&sa, &sa_len);
    if (nread == -1) break;
    buf[nread] = '\0';
    d.len = (size_t)nread;
    assert(-1 != ioctl(fd, SIOCGSTAMPNS, &ts));
    handle_datagram(d);
  }
}

