#ifndef CLIENT_CONTROLLER_GAME_SESSION_H
#define CLIENT_CONTROLLER_GAME_SESSION_H

#include <string>

#include "common/google.h"

class GameSession
{
public:
  GameSession();
  void connect();
  std::string m_server_addr;
};

#endif
