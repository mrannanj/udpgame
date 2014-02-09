#include <iostream>
#include <chrono>

#include <SFML/Network/IpAddress.hpp>

#include "common/config.h"
#include "common/net/dns.h"
#include "common/proto/udpgame.pb.h"
#include "client/controller/game_session.h"
#include "client/controller/input/input.h"
#include "client/view/world_renderer.h"

using namespace std;
using namespace std::chrono;

GameSession::GameSession():
  mClientId(-1),
  mInit(false),
  mRedraw(false),
  mConnection(),
  mPerspective(),
  mWorld(false),
  mInput()
{
}

GameSession::GameSession(const std::string& addr):
  mClientId(-1),
  mInit(false),
  mRedraw(false),
  mConnection(),
  mPerspective(),
  mWorld(false),
  mInput()
{
  if (addr.size() == 0) return;
  mConnection.mSocket->connect(addr, SERVER_PORT);
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
  mInit = true;
  mRedraw = true;
}

void GameSession::tick(Input& input, bool haveFocus) {
  if (!mInit) return;
  mInput = haveFocus ? input : zeroInput();
  mConnection.checkMessages(*this);
  mPerspective.handle_input(mInput);
  mPerspective.tick(mWorld);
}

bool GameSession::handleAMessage(const AMessage& a, const Connection& c) {
  ClientData* cd;
  switch (a.type()) {
    case MessageType::INITIAL_STATE:
      mWorld.setInitialState(a.initial_state());
      mClientId = a.initial_state().client_id();
      sendFrameInput(mInput);
      mRedraw = true;
      return true;
    case MessageType::FRAME_INPUTS:
      mWorld.tick(a.frame_inputs());
      cd = mWorld.client().getByClient(mClientId);
      if (cd) {
        mPerspective.m_follow_id = cd->eid();
        mPerspective.mClientMode = cd->mode();
      }
      sendFrameInput(mInput);
      mRedraw = true;
      return true;
    default:
      return false;
  }
}

Input GameSession::zeroInput() {
  Input i;
  memset(&i, 0, sizeof(i));
  return i;
}

void GameSession::sendFrameInput(Input& i) {
  FrameInput fi;
  fi.set_actions(i.continous_actions);
  fi.set_vertical_delta((float)i.mouse_delta_y * 0.01f);
  fi.set_horizontal_delta((float)i.mouse_delta_x * 0.01f);

  ClientInput ci;
  mWorld.serializeHashes(ci.mutable_hashes());
  ci.set_tick_number(mWorld.mTickNumber + STATIC_FRAME_DELTA);
  ci.mutable_frame_input()->CopyFrom(fi);

  AMessage a;
  a.set_type(MessageType::CLIENT_INPUT);
  a.mutable_client_input()->CopyFrom(ci);
  mConnection.sendMessage(a);
}

void GameSession::draw(const Renderer& r) {
  const glm::mat4& v = mPerspective.view();
  const glm::mat4& p = mPerspective.projection();
  draw_grid(r, mWorld, v, p, mPerspective.m_position);
  draw_units(r, mWorld.physics(), v, p);
  draw_hud(r, mWorld, mPerspective.m_follow_id, mPerspective);

  mRedraw = true;
}
