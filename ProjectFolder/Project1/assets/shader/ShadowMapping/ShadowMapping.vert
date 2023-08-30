#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;


out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;
uniform mat4 MVP;
uniform mat4 NormalMatrix;
uniform bool reverse_normals;

void main()
{
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
     if(reverse_normals)
     {
              vs_out.Normal = mat3(NormalMatrix) * (-1.0 * aNormal);


     }
     else
     {
         vs_out.Normal = mat3(NormalMatrix) * aNormal;

     }
    vs_out.TexCoords = aTexCoords;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    gl_Position = MVP * vec4(aPos, 1.0);
}