#version 130

uniform vec3 quadColor;
out vec4 outColor;

void main()
{
  outColor = vec4(quadColor, 1.0);
}

