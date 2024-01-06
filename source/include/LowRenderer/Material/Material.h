#pragma once
#include<Mathf.h>
#include "Ressources/IResources/IResource.h"
#include "Ressources/Texture/Texture.hpp"
#include "PBRnode.hpp"





struct Phong 
{
	Texture albedo;
	float shininess = 32;
	float ka = 0.5f;
	float kd = 0.5f;
	float ks = 0.5f;
};


class Material
{
public:



	MaterialPBR pbrMaterial;
	Phong phongMaterial;

	Material(){};
	~Material();

private:
};

