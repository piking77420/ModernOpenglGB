#include <LowRenderer/Material/Material.h>



Material::Material(int	_diffuse, int _specular, const float& _shininess) : shininess(_shininess)
{
	diffuse = _diffuse;
	specular = _specular;
}

Material::Material()
{
	diffuse = 0;
	specular = 1;
	shininess = 32;
}

Material::Material(const float& _shiniess)
{
	specular = 1;
	diffuse = 0;
	shininess = _shiniess;
}


Material::~Material()
{

}