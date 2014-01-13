#version 130

uniform mat4 m;
uniform mat4 vp;

in vec3 position;
in vec3 color_;
in vec2 tex_coord_;

out vec3 position_;
out vec3 color;
out vec2 tex_coord;

void main()
{
  mat4 mvp = vp * m;
  position_ = (m * vec4(position, 1.0)).xyz;
  color = color_;
  tex_coord = tex_coord_;
  gl_Position = mvp * vec4(position, 1.0);
}

