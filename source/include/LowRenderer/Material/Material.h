#pragma once
#include<Mathf.h>

class Material
{
public:

	// TO DO ADD TEXTURE FOR DIFFUSE SPECULAR AND DO A BIND MATERIAL
	// EXEMPLE : 
	// Diffuse will be 0 
	// specualr will be always 1
	// so 
	// On where you want to use texture slot activate then bind the material so you will be able to never go furthermore than 30 texture

	// TEXTURE DIFFUSE
	// TEXTURE 

	int diffuse;
	int specular;
	float shininess;

	Material(const float& _shiniess);
	Material(int _diffuse , int _specular, const float& _shininess);
	Material();
	~Material();

private:
};

