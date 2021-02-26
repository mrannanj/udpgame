#pragma once

#include "common/resource_locator.h"
#include "client/view/ft_renderer.h"
#include "client/view/text_renderer.h"
#include "client/view/cube_renderer.h"
#include "client/view/quad_renderer.h"
#include "client/view/texture_manager.h"

class Renderer {
public:
	Renderer();

	ResourceLocator resourceLocator;
	TextureManager texture_manager;
	TextRenderer text_renderer;
	CubeRenderer cube_renderer;
	QuadRenderer quad_renderer;
	FtRenderer ft_renderer;
};
