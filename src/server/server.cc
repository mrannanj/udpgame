#include <iostream>

#include "server/server.h"

constexpr int TICKS_PER_SEC = 20;
constexpr unsigned long NS_PER_TICK = (unsigned long)
  (1000000000 * (1.0f/TICKS_PER_SEC));

Server::Server(int port, int& quit):
  m_tick_timer(NS_PER_TICK),
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

