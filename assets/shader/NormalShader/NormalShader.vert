#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;



out VS_OUT 
{
    vec3 Normal;
	vec2 TexCoords;
    mat4 projection;
	vec3 FragPos;  
	vec3 LightPos;
	
} vs_out;


/*
out vec3 Normalf;
out vec2 TexCoordsf;
out vec3 FragPosf;  
out vec3 LightPosf;
out mat4 projectionf;
*/

//out vec2 TexCoords;
//out vec3 Normal;
//out vec3 FragPos;  
//out vec3 LightPos;


	
uniform mat4 model;
uniform mat4 rotation;
uniform mat4 MVP;
uniform mat4 view;
uniform vec3 lightPos;
uniform mat4 projectionMatrix;





void main()
{
	
	
	//gl_Position = MVP * vec4(aPos, 1.0);
    //vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
	//vs_out.LightPos = vec3(view * vec4(lightPos, 1.0)); 
	//vs_out.Normal = vec3(rotation * vec4(aNormal,1.0)) ;  
	//vs_out.TexCoords = vec2(aTexCoord.x, aTexCoord.y);
	//vs_out.projection = projectionMatrix;
	

	gl_Position = MVP * vec4(aPos, 1.0);
	vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
	vs_out.LightPos = vec3(view * vec4(lightPos, 1.0)); 
	//vs_out.Normal = mat3(rotation) * aNormal;  
	vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;  

	vs_out.TexCoords = vec2(aTexCoord.x, aTexCoord.y);
	vs_out.projection = projectionMatrix;



}