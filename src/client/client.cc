#include "common/config.h"

#include "client/client.h"

Client::Client(unsigned ticks_per_sec, int& quit):
  m_tick_timer(ns_per_tick(ticks_per_sec)),
  m_quit(quit)
{
}

void Client::keepalive()
{
  while (!m_quit)
  {
    m_tick_timer.start_tick();
    m_client_connection.tick();
    m_tick_timer.end_tick();
  }
}

