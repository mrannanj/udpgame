#include <iostream>
#include <chrono>

#include "common/config.h"
#include "common/proto/udpgame.pb.h"
#include "client/controller/game_session.h"
#include "client/controller/input/input.h"
#include "client/view/world_renderer.h"

using namespace std;
using namespace std::chrono;

GameSession::GameSession():
  mInit(false),
  mWorld(false)
{
}

GameSession::GameSession(const std::string& addr):
  mInit(false),
  mConnection(addr),
  mPerspective(),
  mWorld(false)
{
  if (addr.size() == 0) return;
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

bool GameSession::handleAMessage(const AMessage& a, int) {
  ClientData* cd;
  switch (a.type()) {
    case Type::INITIAL_STATE:
      mWorld.setInitialState(a.initial_state());
      mClientId = a.initial_state().client_id();
      sendFrameInput(mInput);
      mRedraw = true;
      return true;
    case Type::FRAME_INPUTS:
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
  ci.set_previous_hash(mWorld.hash());
  ci.set_tick_number(mWorld.mTickNumber + STATIC_FRAME_DELTA);
  ci.mutable_frame_input()->CopyFrom(fi);

  AMessage a;
  a.set_type(Type::CLIENT_INPUT);
  a.mutable_client_input()->CopyFrom(ci);
  mConnection.sendMessage(a);
}

void GameSession::draw(const Renderer& r) {
  r.text_renderer.On();
  r.text_renderer.DrawText(-1.0f, -0.9f, 0.1f,
    mPerspective.pos_string(), Green);
  glm::mat4 vp = mPerspective.get_view_projection_matrix();
  draw_grid(r, mWorld.grid(), vp, mPerspective.m_position);
  draw_units(r, mWorld.physics(), vp);

  float q[] = {
    -0.005f, -0.005f, 0.005f, 0.005f,
    -0.005f, 0.005f, 0.005f, -0.005f
  };
  r.quad_renderer.On();
  set_color(r.quad_renderer.color_uni(), Blue, 1.0f);
  r.quad_renderer.draw_quad(q);
  mRedraw = true;
}
