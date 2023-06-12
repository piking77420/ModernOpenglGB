#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 VP;

void main()
{
    TexCoords = vec2(aTexCoord.x, aTexCoord.y);
    gl_Position = VP * model * vec4(aPos, 1.0);
}   