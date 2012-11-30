#include <iostream>

#include "server/server.h"

Server::Server(uint16_t port, unsigned ticks_per_sec, int& quit):
  m_tick_timer(ns_per_tick(ticks_per_sec)),
  m_udp_socket(port),
  m_quit(quit)
{
}

void Server::listen()
{
  while (!m_quit)
  {
    m_tick_timer.start_tick();
    m_udp_socket.pump_messages();
    m_tick_timer.end_tick();
  }
  std::cout << "quitting" << std::endl;
}

