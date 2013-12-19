#include "common/net/connection.h"
#include "common/config.h"
#include "common/util/die.h"
#include "common/proto/udpgame.pb.h"

#include <fcntl.h>
#include <unistd.h>
#include <cstring>

Connection::Connection(const std::string& addr):
  mPos(0),
  mAddress(addr)
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

Connection::~Connection() {
  close(mSocket);
}
