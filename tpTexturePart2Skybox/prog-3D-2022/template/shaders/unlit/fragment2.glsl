#version 330 core

out vec4 FragColor;

in vec3 coordonneesText;
in vec3 normalText;

uniform vec3 cameraPos;

uniform samplerCube Texture;

void main()
{             
    vec3 I = normalize(coordonneesText - cameraPos);
    vec3 R = reflect(I, normalize(normalText));
    FragColor = vec4(texture(Texture, R).rgb, 1.0);
}