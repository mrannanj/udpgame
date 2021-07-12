#include "client/view/renderer.h"

Renderer::Renderer():
	resourceLocator(),
	texture_manager(resourceLocator),
	text_renderer(resourceLocator, texture_manager[Texture::FONT]),
	cube_renderer(resourceLocator),
	quad_renderer(resourceLocator), ft_renderer(resourceLocator)
{
}
