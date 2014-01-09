#include "common/net/connection.h"
#include "common/config.h"
#include "common/util/die.h"
#include "common/proto/udpgame.pb.h"

#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <netinet/in.h>

Connection::Connection():
  mPos(0),
  mSocket(-1),
  mBuf(nullptr)
{
}

Connection::Connection(const std::string& addr):
  mPos(0),
  mSocket(-1),
  mBuf(nullptr)
{
  if (addr.size() == 0) return;

  mBuf = new char[MAXMSG];
  memset(&mSockaddr, 0, sizeof(mSockaddr));
  mSockaddr.sin_family = AF_INET;
  inet_aton(addr.c_str(), &mSockaddr.sin_addr);
  mSockaddr.sin_port = htons(SERVER_PORT);

  mSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (mSocket == -1) die("socket");

  int on = 1;
  setsockopt(mSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&on, sizeof(int));

  if (-1 == connect(mSocket, (sockaddr*)&mSockaddr, sizeof(mSockaddr)))
    die("connect");

  int flags = fcntl(mSocket, F_GETFL, 0);
  if (-1 == fcntl(mSocket, F_SETFL, flags | O_NONBLOCK))
    die("fcntl");
}

Connection::Connection(int socket, const sockaddr_in& sa):
  mPos(0),
  mSocket(socket),
  mSockaddr(sa)
{
  mBuf = new char[MAXMSG];
  int flags = fcntl(mSocket, F_GETFL, 0);
  if (-1 == fcntl(mSocket, F_SETFL, flags | O_NONBLOCK))
    die("fcntl");
  int on = 1;
  setsockopt(mSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&on, sizeof(int));
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

void really_write(int fd, char* buf, ssize_t count) {
  ssize_t nw;
  for (ssize_t tw = 0; tw < count; tw += nw) {
    nw = write(fd, &buf[tw], count - tw);
    if (nw < 0) {
      if (errno == EINTR)
        continue;
      else
        die("write");
    }
  }
}

void Connection::sendMessage(const AMessage& a) {
  char buf[MAXMSG];
  int byteSize = a.ByteSize();
  assert(MAXMSG >= byteSize);
  ssize_t count = byteSize + sizeof(int);
  int netSize = htonl(byteSize);
  memcpy(buf, &netSize, sizeof(int));
  a.SerializeToArray(&buf[sizeof(int)], byteSize);
  really_write(mSocket, buf, count);
}

std::ostream& operator<<(std::ostream& os, const Connection& c) {
  char* addr = inet_ntoa(c.mSockaddr.sin_addr);
  uint16_t port = ntohs(c.mSockaddr.sin_port);
  return os << "fd: " << c.mSocket << ", addr: " << addr << ":" << port;
}
