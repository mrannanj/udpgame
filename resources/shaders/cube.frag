#version 130

uniform sampler2D texture;

in vec3 position_;
in vec3 color;
in vec2 tex_coord;
in vec3 normal;

out vec4 frag_color;

void main()
{
  vec3 light = vec3(0.0, 30.0, 0.0);
  //vec3 normal = vec3(0.0, 1.0, 0.0);
  vec3 pl = position_ - light;
  float f = 130.0 * dot(normalize(pl), normal)/pow(length(pl),2);
  frag_color = vec4(color, 1.0) * texture2D(texture, tex_coord) * f;
}

