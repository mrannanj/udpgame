#pragma once

#include <set>
#include <vector>
#include <netinet/in.h>

#include "common/net/connection.h"
#include "common/world/world.h"

#define SERVER_BUFSIZE 2048

struct Server {
  Server(int);

  void init();
  void serve();

  int mkFDSet(fd_set*);
  void sendWorldState();

  int mQuit;
  sockaddr_in mListenSA;
  int mListenFD;
  std::vector<Connection> mClients;
  World mWorld;
  AMessagePrinter mPrinter;
};
