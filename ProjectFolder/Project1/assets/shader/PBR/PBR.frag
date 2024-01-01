#version 330 core

in VS_OUT 
{
    vec3 Normal;
	vec2 TexCoords;
	vec3 FragPos;  	
} fs_in;
    
    
    uniform sampler2D albedoMap;
    uniform sampler2D metallicMap;    
    uniform sampler2D roughnessMap;
    uniform sampler2D aoMap;


const float PI = 3.14159;


float distributionGGX(float NdotH,float rougness)
{
    float a  = rougness * rougness; 
    float a2 = a * a;
    float denom = NdotH * NdotH * (a2 - 1.0) + 1.0;
    denom = PI * denom *denom;
    return a2 / max(denom,0.00000001); // not divide by 0
}


float geomeTrySimith(float NdotV,float NdotL,float rougness) 
{
    float r = rougness + 1.0;
    float k = (r *r) / 8.0;
    float ggx1 = NdotV / (NdotV * (1.0 - k ) + k );
    float ggx2 = NdotL / (NdotL * (1.0 - k ) + k );

    return ggx1 * ggx2;
}


vec3 FrenselShiclk(float HdotV,vec3 baseReflectivity)
{
    return baseReflectivity + (1.0 - baseReflectivity) * pow(1.0 - HdotV,5.0);
}

void main()
{

    vec3 albedo = texture(albedoMap,TexCoords).rgb;
    float metallic = texture(metallicMap,TexCoords).r;
    float roughness = texture(roughnessMap,TexCoords).r;
    float ao = texture(aoMap,TexCoords).r;

    vec3 normal = normalize(Normal);
    
    
    vec3 




    FragColor =  vec4(endValue,1) ;
}