#version 130

in vec2 tex_coord;
out vec4 out_color;

uniform vec4 bg_color;
uniform vec4 fg_color;
uniform sampler2D tex;

void main() {
  vec4 tex_color = texture2D(tex, tex_coord);
  if (tex_color.r == 0.0) {
    out_color = bg_color;
  } else {
    out_color = fg_color;
  }
}

