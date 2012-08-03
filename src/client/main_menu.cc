#include "client/main_menu.h"
#include "client/input/input.h"

bool MainMenu::Update(InputReader* input_reader, Real) {
  if (!input_reader) return 0;
  Input input;
  return input_reader->ReadInput(input);
}

void MainMenu::Draw(const Renderer& r) {
  r.text_renderer.DrawText(-1.0f, -0.9f, 0.1f, "UDP Game!");
  r.text_renderer.DrawText(-0.2f, 0.5f, 0.1f, "start");
  r.text_renderer.DrawText(-0.2f, 0.3f, 0.1f, "quit");
}
