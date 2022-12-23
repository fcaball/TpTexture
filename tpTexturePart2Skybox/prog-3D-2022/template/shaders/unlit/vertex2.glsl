#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection; 

out vec3 coordonneesText;
out vec3 normalText;

void main() {
  normalText=mat3(transpose(inverse(model)))*normal;
  coordonneesText=vec3(model*vec4(position,1.0));
  gl_Position = projection * view  * vec4(position.x,-position.y,-position.z,1.0);
}
