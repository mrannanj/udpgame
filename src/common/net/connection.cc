#include "common/net/connection.h"
#include "common/config.h"
#include "common/util/die.h"
#include "common/proto/udpgame.pb.h"

#include <cstring>

#include <SFML/Network/IpAddress.hpp>

Connection::Connection():
  mId(),
  mPos(0),
  mSocket(new sf::TcpSocket()),
  mBuf(MAXMSG),
  mLastFrameOk(0)
{
}

Connection::Connection(Connection&& c):
  mId(c.mId),
  mPos(c.mPos),
  mSocket(std::move(c.mSocket)),
  mBuf(std::move(c.mBuf)),
  mLastFrameOk(c.mLastFrameOk)
{
}

Connection& Connection::operator=(Connection&& c) {
  mId = c.mId;
  mPos = c.mPos;
  mSocket = std::move(c.mSocket);
  mBuf = std::move(c.mBuf);
  mLastFrameOk = c.mLastFrameOk;
  return *this;
}

void Connection::sendMessage(const AMessage& a) {
  char buf[MAXMSG];
  int byteSize = a.ByteSize();
  assert(byteSize > 0);
  assert(MAXMSG >= (size_t)byteSize);
  int count = byteSize + sizeof(int);
  int netSize = htonl(byteSize);
  memcpy(buf, &netSize, sizeof(int));
  a.SerializeToArray(&buf[sizeof(int)], byteSize);

  auto st = mSocket->send(buf, count);
  assert(st == sf::Socket::Status::Done);
}

std::ostream& operator<<(std::ostream& os, const Connection& c) {
  auto addr = c.mSocket->getRemoteAddress();
  uint16_t port = c.mSocket->getRemotePort();
  return os << "id: " << c.mId << " addr: " << addr << ":" << port;
}
