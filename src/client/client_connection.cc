#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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

void ClientConnection::initiate_connection()
{
  char buf[] = "I";
  int fd = m_udp_socket.fd();
  ssize_t n = send(fd, buf, sizeof(buf), 0);
  if (n < 0) perror("sendto");
}

void ClientConnection::tick()
{
  char recv_buf[MAX_MSG+1];
  int fd = m_udp_socket.fd();
  ssize_t n = recv(fd, recv_buf, MAX_MSG, MSG_DONTWAIT);
  if (n < 0) return;
  recv_buf[n] = '\0';
  if (recv_buf[0] == 'P')
  {
    char c = 'P';
    n = send(fd, &c, 1, 0);
    if (n < 0) perror("send");
  }
  else
  {
    std::cout << "unknown message " << recv_buf << std::endl;
  }
}

