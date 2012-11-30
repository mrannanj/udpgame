#include <iostream>

#include "server/server.h"

Server::Server(int port, unsigned ticks_per_sec, int& quit):
  m_tick_timer(ns_per_tick(ticks_per_sec)),
  m_port(port),
  m_quit(quit)
{
}

void Server::listen()
{
  while (!m_quit)
  {
    m_tick_timer.start_tick();
    m_tick_timer.end_tick();
  }
  std::cout << "quitting" << std::endl;
}

