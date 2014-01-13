#version 130

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

in vec3 position_modelspace_;
in vec3 normal_modelspace_;
in vec3 color_;
in vec2 tex_coord_;

out vec3 normal_cameraspace;
out vec3 position_cameraspace;
out vec3 color;
out vec2 tex_coord;

void main()
{
  gl_Position = p * v * m * vec4(position_modelspace_, 1.0);
  normal_cameraspace = normalize((v * m * vec4(normal_modelspace_, 0.0)).xyz);
  position_cameraspace = (v * m * vec4(position_modelspace_, 1.0)).xyz;
  color = color_;
  tex_coord = tex_coord_;
}
