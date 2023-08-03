#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 Normalf;
out vec3 colorf;
out vec2 TexCoordsf;
out vec3 FragPosf;  
out	vec3 LightPosf;

in VS_OUT  
{
    vec3 Normal;
	vec2 TexCoords;
    mat4 projection;
    vec3 FragPos;  
	vec3 LightPos;
} gs_in[];

    
// Default main function
void main()
{
    /*
    gl_Position = gs_in[0].projection * gl_in[0].gl_Position;
    Normalf = gs_in[0].Normal;
    TexCoordsf = gs_in[0].TexCoords;
    FragPosf = gs_in[0].FragPos;
    EmitVertex();

    gl_Position = gs_in[1].projection * gl_in[1].gl_Position;
    Normalf = gs_in[1].Normal;
    TexCoordsf = gs_in[1].TexCoords;
    FragPosf = gs_in[1].FragPos;
    LightPosf = gs_in[1].LightPos;


    EmitVertex();
        
    gl_Position = gs_in[2].projection * gl_in[2].gl_Position;
    Normalf = gs_in[2].Normal;
    TexCoordsf = gs_in[2].TexCoords;
    FragPosf = gs_in[2].FragPos;
    LightPosf = gs_in[2].LightPos;


    EmitVertex();

    EndPrimitive();
    */
}