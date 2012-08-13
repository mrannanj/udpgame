#version 130

uniform mat4 mvp;
in vec2 position;

void main()
{
  gl_Position = mvp * vec4(position, 0.0, 1.0);
}

