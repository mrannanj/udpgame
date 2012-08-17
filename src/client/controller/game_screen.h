#ifndef CLIENT_CONTROLLER_GAME_SCREEN_H
#define CLIENT_CONTROLLER_GAME_SCREEN_H

#include "client/controller/screen.h"
#include "client/controller/perspective.h"
#include "common/world/entity_manager.h"

struct GameScreen : public Screen
{
public:
  GameScreen();
  void Update(InputManager&, float);
  void Draw(const Renderer&);
  void Activate();
private:
  Perspective m_perspective;
  EntityManager m_entity_manager;
};

extern GameScreen g_game_screen;

#endif
