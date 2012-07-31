#version 130

in vec2 position;
in vec2 tex_coord_;
out vec2 tex_coord;

void main() {
  tex_coord = tex_coord_;
  gl_Position = vec4(position, 0.0, 1.0);
}
