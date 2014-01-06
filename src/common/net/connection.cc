#include "common/net/connection.h"
#include "common/config.h"
#include "common/util/die.h"
#include "common/proto/udpgame.pb.h"

#include <fcntl.h>
#include <unistd.h>
#include <cstring>

Connection::Connection():
  mPos(0),
  mSocket(-1)
{
}

Connection::Connection(const std::string& addr):
  mPos(0),
  mSocket(-1)
{
  memset(&mSockaddr, 0, sizeof(mSockaddr));
  mSockaddr.sin_family = AF_INET;
  inet_aton(addr.c_str(), &mSockaddr.sin_addr);
  mSockaddr.sin_port = htons(SERVER_PORT);

  mSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (mSocket == -1) die("socket");

  if (-1 == connect(mSocket, (sockaddr*)&mSockaddr, sizeof(mSockaddr)))
    die("connect");
  if (-1 == fcntl(mSocket, F_SETFL, O_NONBLOCK))
    die("fcntl");
}

Connection::Connection(int socket, const sockaddr_in& sa):
  mPos(0),
  mSocket(socket),
  mSockaddr(sa)
{
  if (-1 == fcntl(mSocket, F_SETFL, O_NONBLOCK))
    die("fcntl");
}

Connection::Connection(Connection&& c):
  mPos(c.mPos),
  mSocket(c.mSocket),
  mSockaddr(c.mSockaddr),
  mBuf()
{
  c.mSocket = -1;
  memcpy(mBuf, c.mBuf, MAXMSG);
}

Connection& Connection::operator=(Connection&& c) {
  mPos = c.mPos;
  mSocket = c.mSocket;
  mSockaddr = c.mSockaddr;
  memcpy(mBuf, c.mBuf, MAXMSG);
  c.mSocket = -1;
  return *this;
}

Connection::~Connection() {
  if (mSocket != -1)
    close(mSocket);
  mSocket = -1;
}

void Connection::sendMessage(const AMessage& a) {
  char buf[MAXMSG];
  short size = a.ByteSize();
  uint16_t netSize = htons(size);
  memcpy(buf, &netSize, sizeof(netSize));
  a.SerializeToArray(&buf[sizeof(netSize)], size);
  write(mSocket, buf, size + sizeof(netSize));
}
