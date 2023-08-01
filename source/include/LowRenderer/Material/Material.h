#pragma once
#include<Mathf.h>

class Material
{
public:

	
	int diffuse;
	int specular;
	float shininess;

	Material(const float& _shiniess);
	Material(int _diffuse , int _specular, const float& _shininess);
	Material();
	~Material();

private:
};

