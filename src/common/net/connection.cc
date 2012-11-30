#include "common/net/connection.h"

Connection::Connection(const sockaddr_in& sa, const timespec& ts):
  m_state(ConnectionState::CONNECTED),
  m_sockaddr(sa),
  m_last_received_time(ts)
{
}

