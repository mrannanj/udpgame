#include "client/view/renderer.h"

Renderer::Renderer()
{
}

void Renderer::Init() {
  GLuint font = texture_manager.LoadImage("resources/images/font.bmp");
  text_renderer.Init(font);
}

void Renderer::Destroy() {
  texture_manager.FreeTextures();
}

