#version 330 core


in VS_OUT 
{
    vec3 Normal;
    vec2 TexCoords;
    vec3 FragPos;  
} fs_in;


// MATERIAL // 
struct PBRAlbedo {
    sampler2D AlbedoTexture;
    vec3 color;
    bool valueTexture;
};

struct PBRMetallic {
    sampler2D MetallicTexture;
    float metallicValue;
    bool valueTexture;
};

struct PBRRoughnes {
    sampler2D RoughnessTexture;
    float RoughnesValue;
    bool valueTexture;
};

struct PBRAmbinatOcclusion {
    sampler2D OcclusionTexture;
    float OcclusionValue;
    bool valueTexture;
};

const float PI = 3.14159265359;

uniform PBRAlbedo albedoNode;
uniform PBRMetallic metallicNode;
uniform PBRRoughnes roughnessNode;
uniform PBRAmbinatOcclusion ambinatOcclusion;

// END MATERIAL 

#define NR_POINT_LIGHTS 10   




// LIGHT

struct DirLight {
    vec3 lightPos;
    vec3 LightDirection;
    vec3 color;
    sampler2D shadowMap;

    float c1;
    float c2;
    float c3;

};

struct PointLight {    
    vec3 position;
    vec3 color;
      
    //samplerCube depthMapCube;
    float far_plane;

}; 


uniform DirLight dirLight;


uniform vec3 viewPos;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int numberOfPointLight;


out vec4 FragColor;

float distributionGGX(vec3 N ,vec3 H, float a)
{
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float nom    = a2;
    float denom  = (NdotH2 * (a2 - 1.0) + 1.0);
    denom        = PI * denom * denom;
	
    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}


vec3 GetAlbedoValue()
{
    if (albedoNode.valueTexture == false)
    {
        return albedoNode.color;
    }

    return texture(albedoNode.AlbedoTexture, fs_in.TexCoords).rgb;
}

float GetMetallicValue()
{
    if (metallicNode.valueTexture == false)
    {
        return metallicNode.metallicValue;
    }

    return texture(metallicNode.MetallicTexture, fs_in.TexCoords).r;
}

float GetRoughnessValue()
{
    if (roughnessNode.valueTexture == false)
    {
        return roughnessNode.RoughnesValue;
    }

    return texture(roughnessNode.RoughnessTexture, fs_in.TexCoords).r;
}

float GetAmbientocclusion()
{
    if (ambinatOcclusion.valueTexture == false)
    {
        return ambinatOcclusion.OcclusionValue;
    }

   return texture(ambinatOcclusion.OcclusionTexture, fs_in.TexCoords).r;
}

void main()
{
    // BASE INPUT // 
    vec3 albedo = GetAlbedoValue();
    float metallic = GetMetallicValue();
    float roughness = GetRoughnessValue();
    float ao = GetAmbientocclusion();
    
    vec3 N = normalize(fs_in.Normal);
    vec3 V = normalize(viewPos - fs_in.FragPos);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);
	           
    // reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < numberOfPointLight; ++i) 
    {
        // calculate per-light radiance
        vec3 L = normalize(pointLights[i].position - fs_in.FragPos);
        vec3 H = normalize(V + L);
        float distance    = length(pointLights[i].position - fs_in.FragPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = pointLights[i].color  *  attenuation;        
        
        // cook-torrance brdf
        float NDF = distributionGGX(N, H, roughness);        
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);       
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;	  
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular     = numerator / denominator;  
            
        // add to outgoing radiance Lo
        float NdotL = max(dot(N, L), 0.0);                
        Lo += (kD * albedo / PI + specular) * radiance * NdotL; 
    }   
  
    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;
	
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  
   
    FragColor = vec4(color, 1.0);


}
    



