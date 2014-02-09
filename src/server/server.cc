#include "server/server.h"
#include "common/config.h"
#include "common/util/die.h"
#include "common/util/timespec.h"
#include "common/util/tick_timer.h"
#include "common/proto/udpgame.pb.h"

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>

#include <iostream>
#include <cassert>
#include <cstring>

using namespace sf;
using namespace std;

Server::Server():
  mSelector(),
  mListener(),
  mIdGen(),
  mClients(),
  mWorld(true),
  mWorldTicker()
{
  mListener.setBlocking(false);
  mListener.listen(SERVER_PORT);
  mSelector.add(mListener);
}

void Server::distributeInputs(unsigned tick) {
  AMessage a;
  a.set_type(MessageType::FRAME_INPUTS);
  a.mutable_frame_inputs()->
    CopyFrom(mWorldTicker.inputsForFrame(tick));
  a.mutable_frame_inputs()->set_tick_number(tick);
  for (Connection& c : mClients)
    c.sendMessage(a);
  mWorldTicker.removeOldFrame(tick);
}

void Server::sendInitialState(Connection& c) {
  AMessage a;
  a.set_type(MessageType::INITIAL_STATE);
  a.mutable_initial_state()->CopyFrom(mWorld.getInitialState());
  a.mutable_initial_state()->set_client_id(c.mId);
  c.sendMessage(a);
}

void Server::serve() {
  TickTimer timer(ms_per_tick);
  sf::Time max_sleep;
  timer.newTick(max_sleep);
  mWorldTicker.setHashes(mWorld.mTickNumber, mWorld.hashes());
  do {
    mSelector.wait(max_sleep);
    acceptNewClient();
    checkClientInput();
    if (timer.isTickTime(max_sleep)) {
      unsigned tickNum = mWorld.mTickNumber + 1;
      mWorldTicker.fillMissingInputs(tickNum, mClients);
      mWorld.tick(mWorldTicker.inputsForFrame(tickNum));
      mWorldTicker.setHashes(tickNum, mWorld.hashes());
      distributeInputs(tickNum);
      mWorldTicker.setCurrentTick(tickNum);
      timer.newTick(max_sleep);
    }
  } while(true);
}

void Server::acceptNewClient() {
  if (mSelector.isReady(mListener)) {
    cout << "new connection ready" << endl;
    mClients.emplace_back();
    Connection& c = mClients.back();
    c.mId = mIdGen.generateId();
    mListener.accept(*c.mSocket);
    mSelector.add(*c.mSocket);
    cout << "accepted " << c << endl;
    c.mLastFrameOk = mWorld.mTickNumber;
    sendInitialState(c);
  }
}

void Server::checkClientInput() {
  for (auto c = mClients.begin(); c != mClients.end();) {
    if (!mSelector.isReady(*c->mSocket)) {
      ++c;
      continue;
    }
    int nread = c->checkMessages(mWorldTicker);
    if (nread <= 0) {
      cout << "disconnected " << *c << endl;
      mSelector.remove(*c->mSocket);
      c = mClients.erase(c);
    } else {
      ++c;
    }
  }
}
