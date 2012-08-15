#ifndef CLIENT_CONTROLLER_GAME_SCREEN_H
#define CLIENT_CONTROLLER_GAME_SCREEN_H

#include "client/controller/screen.h"
#include "client/controller/camera.h"

struct GameScreen : public Screen {
public:
  GameScreen();
  void Update(InputReader&, Real);
  void Draw(const Renderer&);
private:
  Camera m_camera;
};

extern GameScreen g_game_screen;

#endif
