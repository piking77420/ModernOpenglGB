#pragma once
#include<Mathf.h>
#include "Ressources/IResources/IResource.h"
#include "Ressources/Texture/Texture.hpp"

class Material
{
public:

	
	Texture diffuse;
	Texture specular;
	Texture height;
	Texture ambient;
	float shininess = 32;

	Material(){};
	~Material();

private:
};

