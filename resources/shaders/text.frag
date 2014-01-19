#version 110

varying vec2 tex_coord;

uniform vec4 bg_color;
uniform vec4 fg_color;
uniform sampler2D texture;

void main() {
  vec4 tex_color = texture2D(texture, tex_coord);
  if (tex_color.r == 0.0) {
    gl_FragColor = bg_color;
  } else {
    gl_FragColor = fg_color;
  }
}

