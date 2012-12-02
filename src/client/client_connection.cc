#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#include "client/client_connection.h"
#include "common/config.h"
#include "common/die.h"

ClientConnection::ClientConnection():
  m_udp_socket(0)
{
  sockaddr_in sa_server;
  socklen_t sa_len = sizeof(sa_server);
  memset(&sa_server, 0, sizeof(sa_server));
  sa_server.sin_family = AF_INET;
  sa_server.sin_addr.s_addr = inet_addr(SERVER_ADDR);
  sa_server.sin_port = htons(SERVER_PORT);
  if (0 > connect(m_udp_socket.fd(), (sockaddr*)&sa_server, sa_len))
    die("connect");
}

void ClientConnection::tick()
{
  char buf[] = "I";
  int fd = m_udp_socket.fd();
  ssize_t n = send(fd, buf, sizeof(buf), 0);
  if (n < 0) perror("sendto");
}

