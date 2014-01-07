#pragma once

#include <set>
#include <vector>
#include <netinet/in.h>

#include "common/net/connection.h"
#include "common/world/world.h"
#include "common/world/world_ticker.h"

struct Server {
  Server(int);

  void init();
  void serve();

  int mkFDSet(fd_set*);
  void checkClientInput(const fd_set& fds);
  void acceptNewClient(const fd_set& fds);
  void sendInitialState(Connection& c);
  void distributeInputs();

  int mQuit;
  sockaddr_in mListenSA;
  int mListenFD;
  std::vector<Connection> mClients;
  World mWorld;
  WorldTicker mWorldTicker;
};
