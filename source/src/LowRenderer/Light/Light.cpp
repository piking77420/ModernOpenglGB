#include <LowRenderer/Light/Light.h>
#include<Core/DataStructure/Entity/Entity.h>
#include "Ressources/Scene/Scene.h"




unsigned int Light::NbrofPointLight = 0 ;

unsigned int Light::NbrofSpothLight = 0;

void Light::ImguiWindowComponents()
{
}




void Light::SetUniform(Shader* shader) const
{
}

void Light::Update(Scene* Scene)
{

}





Light::Light(Entity& entityAttach, Vector4 _ambiant, Vector4 _diffuse, Vector4 _specular, float _specularStrenght) : Component(entityAttach)  
{
	ambiant = _ambiant;
	diffuse = _diffuse;
	specular = _specular;
	SpecularStrengt = _specularStrenght;
}	

Light::Light(Entity& entityAttach) :ambiant(Vector4::One) , diffuse(Vector4::One) , specular(Vector4::One) ,SpecularStrengt(0.4f) , Component(entityAttach)
{

}



Light::~Light()
{
}