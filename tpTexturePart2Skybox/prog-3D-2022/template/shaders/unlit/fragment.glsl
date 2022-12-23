#version 330 core

out vec4 FragColor;

in vec3 coordonneesText;

uniform samplerCube boxTexture;

void main(){
    FragColor=texture( boxTexture, coordonneesText);
}