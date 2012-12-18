#include <iostream>
#include <cassert>
#include <sys/ioctl.h>
#include <cstring>
#include <errno.h>
#include <algorithm>

#include "server/connection_manager.h"
#include "common/net/udp_socket.h"
#include "common/config.h"

#define BUF_SIZE 512

ConnectionManager::ConnectionManager():
  m_udp_socket(SERVER_PORT),
  m_disc_time{2,0},
  m_ping_time{1,0}
{
}

Connection* ConnectionManager::find_connection(const Datagram& d)
{
  for (Connection& c : m_connections)
  {
    if (d.sa_len == c.sa_len &&
       (0 == memcmp(&c.sa, d.sa, d.sa_len)))
    {
      return &c;
    }
  }
  return NULL;
}

void ConnectionManager::add_connection(const Datagram& d)
{
  Connection c;
  memcpy(&c.ts, d.ts, sizeof(timespec));
  memcpy(&c.sa, d.sa, d.sa_len);
  c.sa_len = d.sa_len;
  c.state = ConnectionState::CONNECTED;
  m_connections.push_back(c);
}

void ConnectionManager::handle_datagram(const Datagram& d)
{
  std::cout << d << std::endl;
  Connection* c = find_connection(d);
  if (c == NULL)
  {
    std::cout << "adding new connection" << std::endl;
    add_connection(d);
  }
  else
  {
    update_timestamp(c, d);
  }
}

void ConnectionManager::update_timestamp(Connection* c, const Datagram& d)
{
  memcpy(&c->ts, d.ts, sizeof(timespec));
  c->state = ConnectionState::CONNECTED;
}

void ConnectionManager::handle_received_datagrams()
{
  int fd = m_udp_socket.fd();
  ssize_t nread = 0;
  char buf[BUF_SIZE];
  sockaddr_storage sa;
  socklen_t sa_len = sizeof(sockaddr_storage);
  timespec ts;
  Datagram d{&sa, 0, buf, 0, &ts};

  for (;;)
  {
    nread = recvfrom(fd, buf, BUF_SIZE, 0,
        (sockaddr*)&sa, &sa_len);
    if (nread == -1) break;
    buf[nread] = '\0';
    d.len = (size_t)nread;
    d.sa_len = sa_len;
    assert(-1 != ioctl(fd, SIOCGSTAMPNS, &ts));
    handle_datagram(d);
  }
}

void ConnectionManager::tick(unsigned long tick)
{
  handle_received_datagrams();
  ping(tick);
}

bool is_disconnected(const Connection& c)
{
  return c.state == ConnectionState::DISCONNECTED;
}

void ConnectionManager::ping(unsigned long tick)
{
  int fd = m_udp_socket.fd();
  char buf[] = "P";
  ssize_t n = 0;
  timespec now, delta;
  clock_gettime(CLOCK_REALTIME, &now);

  for (Connection& c : m_connections)
  {
    if (c.state == ConnectionState::DISCONNECTED) continue;
    delta = now - c.ts;
    if (m_disc_time < delta)
    {
      c.state = ConnectionState::DISCONNECTED;
      std::cout << "disconnect" << std::endl;
    } else if (m_ping_time < delta) {
      n = sendto(fd, buf, sizeof(buf), 0,
          (const sockaddr*)&c.sa, c.sa_len);
      if (n < 0) perror("sendto");
      c.state = ConnectionState::STALE;
      std::cout << "ping" << std::endl;
    } else {
      n = sendto(fd, &tick, sizeof(unsigned long), 0,
          (const sockaddr*)&c.sa, c.sa_len);
      if (n < 0) perror("sendto");
    }
  }
  m_connections.erase(remove_if(m_connections.begin(),
        m_connections.end(), is_disconnected), m_connections.end());
}

