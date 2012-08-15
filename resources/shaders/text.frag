#version 130

in vec2 tex_coord;
out vec4 frag_color;

uniform vec4 bg_color;
uniform vec4 fg_color;
uniform sampler2D texture;

void main() {
  vec4 tex_color = texture2D(texture, tex_coord);
  if (tex_color.r == 0.0) {
    frag_color = bg_color;
  } else {
    frag_color = fg_color;
  }
}

