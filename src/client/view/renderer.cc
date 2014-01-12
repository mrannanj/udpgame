#include "client/view/renderer.h"

Renderer::Renderer():
  texture_manager(),
  text_renderer(texture_manager[Texture::TEXTURE_FONT]),
  cube_renderer(),
  quad_renderer()
{
}

