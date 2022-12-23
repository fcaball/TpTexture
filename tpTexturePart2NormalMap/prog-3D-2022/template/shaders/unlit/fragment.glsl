#version 330 core

out vec4 FragColor;

in vec3 o_positionWorld;
in vec2 o_uv0;
in vec3 tangentLightPos;
in vec3 tangentViewPos;
in vec3 tangentFragmentPos;

uniform sampler2D colorText;
uniform sampler2D normalText;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
    
    vec3 normal=texture(normalText,o_uv0).rgb;
    normal=normalize(normal*2.0-1.0);

    vec3 color=texture(colorText,o_uv0).rgb;

    vec3 ambiant=1.0*color;

    vec3 lightDir=normalize(tangentLightPos -tangentFragmentPos);
    float diff=max(dot(lightDir,normal),0.0);
    vec3 diffuse=diff*color;

    vec3 viewDir=normalize(tangentViewPos-tangentFragmentPos);
    vec3 reflex=reflect(-lightDir,normal);
    vec3 halfway=normalize(lightDir+viewDir);
    float spec=pow(max(dot(normal, halfway),0.0),32.0);
    vec3 specular=vec3(0.2)*spec;

    FragColor=vec4(ambiant+diffuse+specular,1.0);
}
