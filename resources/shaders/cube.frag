#version 130

uniform sampler2D texture;

in vec3 color;
in vec2 tex_coord;

out vec4 frag_color;

void main()
{
  frag_color = vec4(color, 1.0) * texture2D(texture, tex_coord);
}

