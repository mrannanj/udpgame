#version 130

in vec2 tex_coord;
out vec4 out_color;
uniform vec3 color;
uniform sampler2D tex;

void main() {
  out_color = texture2D(tex, tex_coord) * vec4(color, 1.0);
}

