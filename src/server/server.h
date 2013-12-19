#pragma once

#include <set>
#include <netinet/in.h>

#include "common/world/world.h"

#define SERVER_BUFSIZE 1024

struct Server {
  Server(int);

  void init();
  void serve();

  private:
  int mkFDSet(fd_set*);
  void sendWorldState();

  int mQuit;
  sockaddr_in mListenSA;
  int mListenFD;
  std::set<int> mClients;
  World mWorld;
};
