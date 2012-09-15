#ifndef CLIENT_CONTROLLER_GAME_SCREEN_H
#define CLIENT_CONTROLLER_GAME_SCREEN_H

#include <string>

#include "client/controller/screen.h"
#include "client/controller/perspective.h"
#include "common/world/entity_manager.h"
#include "client/controller/game_session.h"

struct GameScreen : public Screen
{
public:
  GameScreen();
  void Update(InputManager&, float);
  void Draw(const Renderer&);
  void Activate();
  std::string m_server_addr;

private:
  Perspective m_perspective;
  EntityManager m_entity_manager;
};

extern GameScreen g_game_screen;

#endif
