#version 130

uniform mat4 v;
uniform sampler2D texture;
uniform vec3 lightPosition[10];
uniform int activeLights;

in vec3 position_cameraspace;
in vec3 normal_cameraspace;
in vec3 color;
in vec2 tex_coord;

out vec4 frag_color;

void main()
{
  float brightness = 0.4;
  for (int i = 0; i < activeLights; ++i) {
    vec3 light_cameraspace = (v * vec4(lightPosition[i], 1.0)).xyz;

    vec3 eyedir_camspace = vec3(0,0,0) - position_cameraspace;
    vec3 lightdir_camspace = light_cameraspace + eyedir_camspace;

    float len = length(position_cameraspace - light_cameraspace);
    vec3 n = normalize(normal_cameraspace);
    vec3 l = normalize(lightdir_camspace);
    brightness += clamp(dot(n, l), 0.0, 1.0)/len;
  }
  frag_color = vec4(color, 1.0) * texture2D(texture, tex_coord) * brightness;
}
