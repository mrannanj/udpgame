#version 110

attribute vec2 position;
attribute vec2 tex_coord_;
varying vec2 tex_coord;

void main() {
  tex_coord = tex_coord_;
  gl_Position = vec4(position, 0.0, 1.0);
}
