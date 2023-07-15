#version 330 core
layout (location = 0) in vec3 aPos;



out vec4 Color;


uniform mat4 Ortho;



uniform mat4 model;


void main()
{
   gl_Position = Ortho  * model * vec4(aPos, 1.0);	

}