#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 coordonneesText;


void main() {
  
  coordonneesText=position;
  gl_Position = projection * view  * vec4(position.x,-position.y,-position.z,1.0);
}
