#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec2 uv0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 o_positionWorld;
out vec2 o_uv0;
out vec3 tangentLightPos;
out vec3 tangentViewPos;
out vec3 tangentFragmentPos;

uniform vec3 viewPos;
uniform vec3 lightPos;

void main() {
  o_positionWorld=vec3(model*vec4(position,1.0));
  o_uv0 = uv0;

  mat3 normalMatrix = transpose(inverse(mat3(model)));
  vec3 tang=normalize(normalMatrix*tangent);
  vec3 norm=normalize(normalMatrix*normal);
  tang=normalize(tang-dot(tang,norm)*norm);
  vec3 bitang=cross(norm,tang);

  mat3 tangBitangNorm=transpose(mat3(tang,bitang,norm));
  tangentLightPos=tangBitangNorm*lightPos;
  tangentViewPos=tangBitangNorm*viewPos;
  tangentFragmentPos=tangBitangNorm*o_positionWorld;

  gl_Position = projection * view * model * vec4(position,1.0);
}
