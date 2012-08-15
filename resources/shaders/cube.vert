#version 130

uniform mat4 mvp;
in vec3 position;
in vec3 color_;
in vec2 tex_coord_;

out vec3 color;
out vec2 tex_coord;

void main()
{
  color = color_;
  tex_coord = tex_coord_;
  gl_Position = mvp * vec4(position, 1.0);
}

