#include "client/main_menu.h"

bool MainMenu::Update(InputReader* input, Real) {
  if (!input) return 0;
  Actions a;
  return input->ReadInput(a);
}

void MainMenu::Draw(const Renderer& r) {
  r.text_renderer.DrawText(-1.0f, -0.9f, 0.1f, "UDP Game!");
}
