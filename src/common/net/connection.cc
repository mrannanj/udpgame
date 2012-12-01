#include "common/net/connection.h"

Connection::Connection(const sockaddr_in& sa, const timespec& ts):
  m_state(ConnectionState::CONNECTED),
  m_sockaddr(sa),
  m_last_received_time(ts)
{
}

ConnectionState Connection::state() const
{
  return m_state;
}

std::ostream& operator<<(std::ostream& out, const Connection& c)
{
  return out << "connection";
}

