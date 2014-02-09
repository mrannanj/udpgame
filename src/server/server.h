#pragma once

#include <set>
#include <vector>

#include <SFML/Network/SocketSelector.hpp>
#include <SFML/Network/TcpListener.hpp>

#include "common/util/id_generator.h"
#include "common/net/connection.h"
#include "common/world/world.h"
#include "server/world_ticker.h"

struct Server {
  Server();

  void serve();

  int mkFDSet();
  void disconnectSlowClients();
  void checkClientInput();
  void acceptNewClient();
  void sendInitialState(Connection&);
  void distributeInputs(unsigned);

  sf::SocketSelector mSelector;
  sf::TcpListener mListener;
  IdGen<int> mIdGen;

//  int mQuit;
//  sockaddr_in mListenSA;
//  int mListenFD;
  std::vector<Connection> mClients;
  World mWorld;
  WorldTicker mWorldTicker;
};
