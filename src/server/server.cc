#include <iostream>

#include "server/server.h"

Server::Server(unsigned ticks_per_sec, int& quit):
  m_tick_timer(ns_per_tick(ticks_per_sec)),
  m_quit(quit)
{
}

void Server::listen()
{
  while (!m_quit)
  {
    m_tick_timer.start_tick();
    m_connection_manager.tick();
    m_tick_timer.end_tick();
  }
  std::cout << "quitting" << std::endl;
}

