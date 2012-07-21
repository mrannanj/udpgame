#include <SDL.h>

#include "client/input/input_reader.h"
#include "client/view/graphics.h"
#include "common/world/world.h"

int main(void)
{
  Actions actions;
  InputReader input_reader;
  Graphics graphics;
  World world;

  graphics.Init();
  world.Init();
  input_reader.Init();
  EntityId player_id = world.SpawnEntity();

  for (;;) {
    if (input_reader.ReadInput(actions)) break;
    world.SetEntityInput(player_id, actions);
    world.Tick(0.1f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    graphics.DrawWorld(world);
    SDL_GL_SwapBuffers();
  }

  graphics.Destroy();
  SDL_Quit();
  return 0;
}
