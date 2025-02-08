#version 330 core

in vec3 aPos;
in vec2 aTex;

uniform mat4 mvp;

out vec2 texCoord;
out vec3 FragPos;

void main()
{
    FragPos = aPos;
    gl_Position = mvp * vec4(aPos, 1.0);

    texCoord = aTex;
}