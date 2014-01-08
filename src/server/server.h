#pragma once

#include <set>
#include <vector>
#include <netinet/in.h>

#include "common/net/connection.h"
#include "common/world/world.h"
#include "server/world_ticker.h"

struct Server {
  Server(int);

  void init();
  void serve();

  int mkFDSet(fd_set*);
  void disconnectSlowClients();
  void checkClientInput(const fd_set&);
  void acceptNewClient(const fd_set&);
  void sendInitialState(Connection&);
  void distributeInputs(unsigned);

  int mQuit;
  sockaddr_in mListenSA;
  int mListenFD;
  std::vector<Connection> mClients;
  World mWorld;
  WorldTicker mWorldTicker;
};
