#include <iostream>
#include "client/controller/game_session.h"

using namespace std;

GameSession::GameSession(const std::string& addr):
  mConnection(addr),
  mPerspective(),
  mWorld()
{
}

void GameSession::tick(Input& input) {
  mConnection.checkMessages(mWorld);
  mPerspective.handle_input(input);
  mPerspective.tick();
}

GameSession* g_game_session = nullptr;
