#pragma once

#include <string>

#include "common/platform.h"
#include "client/view/color.h"
#include "client/view/shader.h"

class TextRenderer : public Shader {
public:
	TextRenderer(const ResourceLocator&, GLuint);
	TextRenderer(const TextRenderer&) = delete;
	TextRenderer& operator=(const TextRenderer&) = delete;

	void On() const;
	void DrawText(float, float, float, const std::string&,
		      const Color&) const;

private:
	GLuint m_font_texture;
	size_t vertex_elem_size_;
	GLint bg_color_uni_;
};
