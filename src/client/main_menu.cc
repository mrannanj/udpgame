#include <iostream>
#include "client/view/window.h"
#include "client/main_menu.h"
#include "client/input/input.h"

MainMenu::MainMenu():
  quit_(-0.2f, 0.3f, 0.1f, "quit"),
  start_(-0.2f, 0.5f, 0.1f, "start")
{
}

bool MainMenu::Update(InputReader* input_reader, Real) {
  if (!input_reader) return 0;
  Input input;
  bool quit = input_reader->ReadInput(input);
  if (quit) return true;
  quit_.Update(input);
  start_.Update(input);
  return quit;
}

void MainMenu::Draw(const Renderer& r) {
  quit_.Draw(r);
  start_.Draw(r);
  r.text_renderer.DrawText(-1.0f, -0.9f, 0.1f, "UDP Game!", Blue);
}
