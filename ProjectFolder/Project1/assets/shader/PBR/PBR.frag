#version 330 core


in VS_OUT 
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
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
    int FilterSize;


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

uniform samplerCube environmentMap;


// IBL
uniform samplerCube irradianceMap;
uniform float irridanceFactor;

out vec4 FragColor;


float ShadowCalculationDirectionLight(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
        



     // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
     if(projCoords.z > 1.0)
     {
          return 0.0;
     }


    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(dirLight.shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = fs_in.Normal;
    //vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, dirLight.LightDirection)), 0.005);
    // check whether current frag pos is in shadow
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;



    // PCF   
    vec2 texelSize = 1.0 / textureSize(dirLight.shadowMap, 0);
    int halfFilter = dirLight.FilterSize / 2 ;

    for(int x = -halfFilter; x <= halfFilter + dirLight.FilterSize; x++)
    {
        for(int y = -halfFilter; y <= halfFilter + dirLight.FilterSize; y++)
        {
            vec2 offSet = vec2(x, y) * texelSize;
            float pcfDepth = texture(dirLight.shadowMap, projCoords.xy + offSet).x; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }

    shadow /= float(pow(dirLight.FilterSize,2));
    
  
        
    return shadow;
}



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
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
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



vec3 ComputePointLight(PointLight pointLight,vec3 V,vec3 N ,vec3 F0,vec3 albedo, float roughness,float metallic)
{
        vec3 Lo = vec3(0.0);
        // calculate per-light radiance
        vec3 L = normalize(pointLight.position - fs_in.FragPos);
        vec3 H = normalize(V + L);
        float distance    = length(pointLight.position - fs_in.FragPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = pointLight.color  *  attenuation;        
        
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

        return Lo;
}

vec3 ComputeDirectionalLight(DirLight light,vec3 V,vec3 N ,vec3 F0,vec3 albedo, float roughness,float metallic)
{
        vec3 Lo = vec3(0.0);

        vec3 L = normalize(light.lightPos - fs_in.FragPos);
        vec3 H = normalize(V + L);
        float distance    = length(light.lightPos - fs_in.FragPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = light.color  *  attenuation;        
        
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
        // calculate shadow
        float shadow = ShadowCalculationDirectionLight(fs_in.FragPosLightSpace);
        float shadowf = (1.0 - shadow);
        Lo *= shadowf;

    return Lo;
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

    Lo += ComputeDirectionalLight(dirLight,V,N,F0,albedo,roughness,metallic);

    for(int i = 0; i < numberOfPointLight; ++i) 
    {
        Lo += ComputePointLight(pointLights[i],V,N,F0,albedo,roughness,metallic);
    }   
    
    
        // ambient lighting (we now use IBL as the ambient term)
    vec3 kS = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness); 
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;	  
    vec3 irradiance = texture(irradianceMap, N).rgb * irridanceFactor ;
    vec3 diffuse      = irradiance * albedo;
    vec3 ambient = (kD * diffuse) * ao;
    vec3 color = ambient + Lo;

    
    
    //vec3 ambient = vec3(0.03) * albedo * ao;
    //vec3 color = ambient + Lo;
	

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  
   
    FragColor = vec4(color, 1.0);


}
    



