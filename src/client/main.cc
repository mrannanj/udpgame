#include <SDL.h>

#include "client/view/video.h"
#include "client/game.h"

int main(void)
{
  InitVideo();

  Game game;
  game.Init();
  game.Run();

  SDL_Quit();
  return 0;
}
