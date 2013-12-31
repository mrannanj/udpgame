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
  mWorld()
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

void Server::sendWorldState() {
  char buf[SERVER_BUFSIZE];
  AMessage a;
  a.set_type(Type::WORLD_STATE);
  WorldState w = mWorld.getState();
  a.mutable_world_state()->CopyFrom(w);
  short size = a.ByteSize();
  uint16_t netSize = htons(size);
  memcpy(buf, &netSize, sizeof(netSize));
  a.SerializeToArray(&buf[sizeof(netSize)], size);
  for (const Connection& c : mClients) {
    write(c.mSocket, buf, size + sizeof(netSize));
  }
}

void Server::serve() {
  char buf[SERVER_BUFSIZE];
  fd_set fds;
  for (int i = 0;; ++i) {
    sendWorldState();
    if (i % 5 == 0) mWorld.spawn_entity();
    mWorld.tick(sec_per_ticks);
    int nfds = mkFDSet(&fds);
    timeval tv = {0, 1000000/TICKS_PER_SEC};
    if (-1 == select(nfds, &fds, nullptr, nullptr, &tv))
      perror("read");

    for (auto it = mClients.begin(); it != mClients.end();) {
      Connection& c = *it;
      if (!FD_ISSET(c.mSocket, &fds)) {
        ++it;
        continue;
      }
      cout << "message from client" << endl;
      ssize_t n = read(c.mSocket, buf, SERVER_BUFSIZE);
      if (n == 0) {
        cout << "client disconnect" << endl;
        it = mClients.erase(it);
      } else if (n == -1) {
        perror("read");
        it = mClients.erase(it);
      } else {
        ++it;
      }
    }
    if (FD_ISSET(mListenFD, &fds)) {
      sockaddr_in sa;
      socklen_t sa_len;
      int client = accept(mListenFD, (sockaddr*)&sa, &sa_len);
      if (client != -1) {
        cout << "client connected" << endl;
        mClients.emplace_back(client, sa);
      }
    }
    if (FD_ISSET(mQuit, &fds)) break;
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
