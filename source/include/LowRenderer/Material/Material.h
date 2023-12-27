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
	float ka = 0.5f;
	float kd = 0.5f;
	float ks = 0.5f;

	Material(){};
	~Material();

private:
};

