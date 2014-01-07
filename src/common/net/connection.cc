#include "common/net/connection.h"
#include "common/config.h"
#include "common/util/die.h"
#include "common/proto/udpgame.pb.h"

#include <fcntl.h>
#include <unistd.h>
#include <cstring>

Connection::Connection():
  mPos(0),
  mSocket(-1),
  mBuf(nullptr)
{
}

Connection::Connection(const std::string& addr):
  mPos(0),
  mSocket(-1)
{
  mBuf = new char[MAXMSG];
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
  mBuf = new char[MAXMSG];
  if (-1 == fcntl(mSocket, F_SETFL, O_NONBLOCK))
    die("fcntl");
}

Connection::Connection(Connection&& c):
  mPos(c.mPos),
  mSocket(c.mSocket),
  mSockaddr(c.mSockaddr),
  mBuf(c.mBuf)
{
  c.mSocket = -1;
  c.mBuf = nullptr;
}

Connection& Connection::operator=(Connection&& c) {
  mPos = c.mPos;
  mSocket = c.mSocket;
  mSockaddr = c.mSockaddr;
  mBuf = c.mBuf;
  c.mSocket = -1;
  c.mBuf = nullptr;
  return *this;
}

Connection::~Connection() {
  if (mSocket != -1)
    close(mSocket);
  mSocket = -1;
  if (mBuf != nullptr)
    delete[] mBuf;
  mBuf = nullptr;
}

void Connection::sendMessage(const AMessage& a) {
  char buf[MAXMSG];
  int byteSize = a.ByteSize();
  assert(MAXMSG >= byteSize);
  int netSize = htonl(byteSize);
  memcpy(buf, &netSize, sizeof(int));
  a.SerializeToArray(&buf[sizeof(int)], byteSize);
  write(mSocket, buf, byteSize + sizeof(int));
}

std::ostream& operator<<(std::ostream& os, const Connection& c) {
  char* addr = inet_ntoa(c.mSockaddr.sin_addr);
  uint16_t port = ntohs(c.mSockaddr.sin_port);
  return os << "fd: " << c.mSocket << ", addr: " << addr << ":" << port;
}
