#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 Normal;
out vec2 TexCoords;
out vec3 FragPos;  
out	vec3 LightPos;



out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} gs_in[];
    
// Default main function
void main()
{
    
    gl_Position = gl_in[0].gl_Position;
    Normal = gs_in[0].Normal;
    TexCoords = gs_in[0].TexCoords;
    FragPos = gs_in[0].FragPos;
    EmitVertex();

    gl_Position =  gl_in[1].gl_Position;
    Normal = gs_in[1].Normal;
    TexCoords = gs_in[1].TexCoords;
    FragPos = gs_in[1].FragPos;


    EmitVertex();
        
    gl_Position =  gl_in[2].gl_Position;
    Normal = gs_in[2].Normal;
    TexCoords = gs_in[2].TexCoords;
    FragPos = gs_in[2].FragPos;


    EmitVertex();

    EndPrimitive();
    
}