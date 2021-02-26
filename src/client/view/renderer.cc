#include "client/view/renderer.h"

Renderer::Renderer():
	resourceLocator(),
	texture_manager(resourceLocator),
	text_renderer(resourceLocator, texture_manager[Texture::TEXTURE_FONT]),
	cube_renderer(resourceLocator),
	quad_renderer(resourceLocator), ft_renderer(resourceLocator)
{
}
