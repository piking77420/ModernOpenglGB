#version 330 core
out vec4 FragColor;
#define NR_POINT_LIGHTS 10   
#define NR_SPOTHLIGHT_LIGHTS 100   

struct Material
{
    vec3 MPos;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
    float ka;
    float kd;
    float ks;
};



struct PointLight {    
    vec3 position;
    vec3 color;
       

    //samplerCube depthMapCube;
    float far_plane;

}; 

struct DirLight {
    vec3 lightPos;
    vec3 LightDirection;
    vec3 color;
    sampler2D shadowMap;

    float c1;
    float c2;
    float c3;

};  

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 color;

    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
  

};


in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform vec3 viewPos;


uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_POINT_LIGHTS];
uniform Material material;

uniform int numberOfPointLight;
uniform int numberOfSpothLight;

float ShadowCalculationDirectionLight(vec4 fragPosLightSpace)
{
     // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(dirLight.shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    //vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, dirLight.LightDirection)), 0.005);
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(dirLight.shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(dirLight.shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}



// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

/*
float ShadowCalculationPointLight(PointLight light,vec3 fragPos)
{
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - light.position;
    // use the fragment to light vector to sample from the depth map    
    // float closestDepth = texture(depthMap, fragToLight).r;
    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
    // closestDepth *= far_plane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // test for shadows
    // float bias = 0.05; // we use a much larger bias since depth is now in [near_plane, far_plane] range
    // float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;
    // PCF
    // float shadow = 0.0;
    // float bias = 0.05; 
    // float samples = 4.0;
    // float offset = 0.1;
    // for(float x = -offset; x < offset; x += offset / (samples * 0.5))
    // {
        // for(float y = -offset; y < offset; y += offset / (samples * 0.5))
        // {
            // for(float z = -offset; z < offset; z += offset / (samples * 0.5))
            // {
                // float closestDepth = texture(depthMap, fragToLight + vec3(x, y, z)).r; // use lightdir to lookup cubemap
                // closestDepth *= far_plane;   // Undo mapping [0;1]
                // if(currentDepth - bias > closestDepth)
                    // shadow += 1.0;
            // }
        // }
    // }
    // shadow /= (samples * samples * samples);
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / light.far_plane)) / 25.0;
   /* for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(light.depthMapCube, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= light.far_plane;   // undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
        
    // display closestDepth as debug (to visualize depth cubemap)
    // FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
        
    return shadow;
}
*/

vec3 DirectionnalLightCalcul()
{
    // PixelColor
    vec3 BaseColor = texture(material.diffuse, fs_in.TexCoords).rgb;


    vec3 lightColor = dirLight.color;

    // ambient
    float ambient =  material.ka;


    // diffuse
    vec3 normal = normalize(fs_in.Normal);

    vec3 lightDir = normalize(dirLight.lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    //float diff = max(dot(dirLight.LightDirection, normal), 0.0);
    float diffuse = diff * material.kd ;


    // specular
    float spec = 0.0;
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 halfwayDir = normalize(dirLight.LightDirection + viewDir);  

    vec3 reflectDir = reflect(-dirLight.LightDirection, normal);
    spec = pow(max(dot(normal, halfwayDir), 0.0),material.shininess);

    float specular = spec * material.ks;

    

    

    // calculate shadow
    float shadow = ShadowCalculationDirectionLight(fs_in.FragPosLightSpace);
    float shadowf = (1.0 - shadow);

    
    vec3 lighting =  ( (diffuse  + ambient) + specular ) * lightColor * shadowf; 
    BaseColor *= lighting;
        
    return BaseColor;
}

vec3 PointLightCalcul(PointLight light)
{
  // PixelColor
    vec3 BaseColor = texture(material.diffuse, fs_in.TexCoords).rgb;


    vec3 lightColor = light.color;

    // ambient
    float ambient =  material.ka;


    // diffuse
    vec3 normal = normalize(fs_in.Normal);

    vec3 lightDir = normalize(light.position - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    //float diff = max(dot(dirLight.LightDirection, normal), 0.0);
    float diffuse = diff * material.kd ;


    // specular
    float spec = 0.0;
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);  

    vec3 reflectDir = reflect(-lightDir, normal);
    spec = pow(max(dot(normal, halfwayDir), 0.0),material.shininess);

    float specular = spec * material.ks;

    
    // attenuation
    float pixelLightDistance = distance(fs_in.FragPos , light.position);
    float viewPosDistance = distance(fs_in.FragPos,viewPos);

    float fAtt = 1.0/ (viewPosDistance +  pixelLightDistance) ;

    fAtt = min(fAtt,1.0);
     
    vec3 lighting =  ( (diffuse * fAtt + ambient) + specular * fAtt) * lightColor; 
    BaseColor *= lighting;
        
    return BaseColor;
}



void main()
{           
     vec3 endresult = vec3(0.0);
    // endresult += DirectionnalLightCalcul();
    
    for(int i = 0 ; i < numberOfPointLight;i++)
    {
       endresult += PointLightCalcul(pointLights[i]);
    }

    FragColor = vec4(endresult, 1.0);
}