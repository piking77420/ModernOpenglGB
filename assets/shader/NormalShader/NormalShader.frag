#version 330 core
out vec4 FragColor;

#define NR_POINT_LIGHTS 10   
#define NR_SPOTH_LIGHTS 10   


struct Material
{
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
};


struct DirLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;

};  

struct PointLight {    
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;


        
    float constant;
    float linear;
    float quadratic;
};  

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;     

};



    

in vec2 TexCoordsf;
in vec3 Normalf;  
in vec3 FragPosf;  
in vec3 LightPosf;

uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight[NR_POINT_LIGHTS];
uniform DirLight dirLight;


uniform  int nbrOfPointLight;
uniform  int nbrOfSpothLightLight;


uniform sampler2D shadowMap;

uniform vec3 viewPos;
uniform Material material;


vec3 CalculatePointLight(PointLight light , vec3 normal , vec3 fragPos , vec3 viewDir )
{
    // Determiante Light direction
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse 
    float diff = max(dot(normal, lightDir), 0.0);
    // specular 
    vec3 reflectDir = reflect(-lightDir, normal);
    // Calculate attenuation
    float Distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * Distance + light.quadratic  * Distance);    
    
    float spec = 0 ;
    
    vec3 halfwayDir = normalize(lightDir + viewDir);
     spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    
  
    


    // result for eachType
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoordsf));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoordsf));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoordsf));
    // end result
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}



vec3 Directionnal(DirLight light , vec3 normal , vec3 viewDir)
{
    vec3 lightdir = normalize(-light.direction);
    vec3 reflectDir = reflect(-lightdir,normal);

    // diffuse light
    float diff = max(dot(normal,lightdir),0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoordsf));


    // Specular Light
    float spec = 0 ;
    vec3 halfwayDir = normalize(lightdir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    
   
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoordsf));

    // ambiant light
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoordsf));
    
    return ambient + diffuse + specular;
}

vec3 SpothLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse Light
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoordsf));
    // specular Light
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = 0;
    
    vec3 halfwayDir = normalize(lightDir + viewDir);    
    spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    
   
    // attenuation
    float Distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * Distance + light.quadratic * Distance); 
    

    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);


    // end result
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoordsf));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoordsf));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}


void main()
{


  
    vec3 endValue = vec3(0.0);
    vec3 norm = normalize(Normalf);
    vec3 viewDir = normalize(viewPos - FragPosf);

    endValue = Directionnal(dirLight,norm,viewDir);

    for(int i = 0 ; i < nbrOfPointLight;i++)
    {
        endValue += CalculatePointLight(pointLights[i],norm,FragPosf,viewDir);

    } 

    for(int k = 0 ; k < nbrOfSpothLightLight;k++)
    {
     endValue += SpothLight(spotLight[k],norm,FragPosf,viewDir);
    } 


    FragColor =  vec4(endValue,1) ;// texture(ourTexture, TexCoord);
}