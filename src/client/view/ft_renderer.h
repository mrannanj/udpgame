#pragma once

#include <string>
#include <map>

#include "common/include/glm.h"
#include "common/platform.h"
#include "client/view/color.h"
#include "client/view/shader.h"
#include "client/view/hitbox_2d.h"

struct CharGlyph {
	unsigned int textureID; // ID handle of the glyph texture
	glm::ivec2 size;        // Size of glyph
	glm::ivec2 bearing;     // Offset from baseline to left/top of glyph
	long int advance;       // Offset to advance to next glyph
};

class FtRenderer : public Shader {
public:
	FtRenderer(const ResourceLocator&);
	FtRenderer(const FtRenderer&) = delete;
	FtRenderer& operator=(const FtRenderer&) = delete;

	void On() const;
	struct Hitbox2D DrawText(float, float, float, const std::string&,
				 const Color&) const;

private:
	std::map<char, CharGlyph> m_chars;
};
