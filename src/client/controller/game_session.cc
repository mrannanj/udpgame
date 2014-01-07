#include <iostream>
#include <chrono>

#include "common/proto/udpgame.pb.h"
#include "client/controller/game_session.h"
#include "common/world/components/inputc.h"

using namespace std;
using namespace std::chrono;

GameSession::GameSession():
  mInit(false)
{
}

GameSession::GameSession(const std::string& addr):
  mInit(true),
  mConnection(addr),
  mPerspective(),
  mWorld()
{
  cout << "connected to " << mConnection << endl;
  system_clock::time_point t1 = system_clock::now();
  while (!mWorld.mInit) {
    mConnection.checkMessages(*this);
    system_clock::time_point t2 = system_clock::now();

    if (t2-t1 >= chrono::seconds(1)) {
      cout << "Failed to get initial state from server, exiting" << endl;
      exit(EXIT_FAILURE);
    }
  }
}

void GameSession::tick(Input& input) {
  mConnection.checkMessages(*this);
  mPerspective.handle_input(input);
  mPerspective.tick(mWorld);
  sendFrameInput(input);
}

bool GameSession::handleAMessage(const AMessage& a, int) {
  switch (a.type()) {
    case Type::WORLD_STATE:
      mWorld.setState(a.world_state());
      mPerspective.m_follow_id = a.world_state().owned_id();
      mPerspective.m_freelook = a.world_state().client_mode();
      return true;
    case Type::INITIAL_STATE:
      mWorld.setInitialState(a.initial_state());
      return true;
    default:
      return false;
  }
}

void GameSession::sendFrameInput(Input& i) {
  InputC ic(i);
  ClientInput ci;
  ci.set_tick_number(mWorld.mTickNumber + 1);
  ci.set_actions(ic.actions);
  ci.set_verical_delta(ic.vertical_angle_delta);
  ci.set_horizontal_delta(ic.horizontal_angle_delta);
  AMessage a;
  a.set_type(Type::CLIENT_INPUT);
  a.mutable_input()->CopyFrom(ci);
  mConnection.sendMessage(a);
}
