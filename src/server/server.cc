#include "server/server.h"
#include "common/config.h"
#include "common/util/die.h"
#include "common/proto/udpgame.pb.h"

#include <iostream>
#include <cassert>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

using namespace std;

Server::Server(int quit):
  mQuit(quit),
  mListenSA(),
  mListenFD(-1),
  mClients(),
  mWorld(),
  mWorldTicker(mClients.size(), mWorld.mTickNumber)
{
  mWorld.defaultWorld();
}

void Server::init() {
  memset(&mListenSA, 0, sizeof(mListenSA));
  mListenSA.sin_family = AF_INET;
  mListenSA.sin_addr.s_addr = INADDR_ANY;
  mListenSA.sin_port = htons(SERVER_PORT);
  mListenFD = socket(AF_INET, SOCK_STREAM, 0);
  if (mListenFD == -1) die("socket");

  int on = 1;
  if (0 != setsockopt(mListenFD, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
    die("setsockopt");
  if (0 != bind(mListenFD, (const sockaddr*)&mListenSA, sizeof(mListenSA)))
    die("bind");
  if (0 != listen(mListenFD, 10))
    die("listen");
  if (-1 == fcntl(mListenFD, F_SETFL, O_NONBLOCK))
    die("fcntl");
}

void Server::broadcastWorldState() {
  AMessage a;
  a.set_type(Type::WORLD_STATE);
  WorldState w = mWorld.getState();
  a.mutable_world_state()->CopyFrom(w);
  for (Connection& c : mClients) {
    ClientData* cd = mWorld.client().getByClient(c.mSocket);
    assert(cd != nullptr);
    a.mutable_world_state()->set_owned_id(cd->id);
    a.mutable_world_state()->set_client_mode(cd->mode);
    c.sendMessage(a);
  }
}

void Server::sendWorldState(Connection& c) {
  AMessage a;
  a.set_type(Type::WORLD_STATE);
  WorldState w = mWorld.getState();
  a.mutable_world_state()->CopyFrom(w);
  ClientData* cd = mWorld.client().getByClient(c.mSocket);
  assert(cd != nullptr);
  a.mutable_world_state()->set_owned_id(cd->id);
  a.mutable_world_state()->set_client_mode(cd->mode);
  c.sendMessage(a);
}

void Server::serve() {
  fd_set fds;
  do {
    int nfds = mkFDSet(&fds);
    if (-1 == select(nfds, &fds, nullptr, nullptr, nullptr)) die("select");
    acceptNewClient(fds);
    checkClientInput(fds);

    if (mWorldTicker.ok()) {
      mWorld.tick(sec_per_ticks, mWorldTicker.mInputs);
      mWorldTicker.nextWait(mClients.size(), mWorld.mTickNumber + 1);
      broadcastWorldState();
    }
  } while(!FD_ISSET(mQuit, &fds));
}

void Server::acceptNewClient(const fd_set& fds) {
  if (FD_ISSET(mListenFD, &fds)) {
    sockaddr_in sa;
    socklen_t sa_len;
    int client = accept(mListenFD, (sockaddr*)&sa, &sa_len);
    if (client != -1) {
      mClients.emplace_back(client, sa);
      Connection& c = mClients.back();
      mWorld.connected(c.mSocket);
      sendWorldState(c);
      cout << c << " connected" << endl;
    }
  }
}

void Server::checkClientInput(const fd_set& fds) {
  for (auto it = mClients.begin(); it != mClients.end();) {
    Connection& c = *it;
    if (!FD_ISSET(c.mSocket, &fds)) {
      ++it;
      continue;
    }
    ssize_t nread = c.checkMessages(mWorldTicker);
    if (nread <= 0) {
      cout << c << " disconnected" << endl;
      mWorld.disconnected(c.mSocket);
      it = mClients.erase(it);
    } else {
      ++it;
    }
  }
}

int Server::mkFDSet(fd_set* set) {
  FD_ZERO(set);
  FD_SET(mQuit, set);
  FD_SET(mListenFD, set);
  int m = max(mListenFD, mQuit);
  for (const Connection& c : mClients) {
    m = max(m, c.mSocket);
    FD_SET(c.mSocket, set);
  }
  return m + 1;
}
