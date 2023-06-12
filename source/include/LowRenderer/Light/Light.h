#pragma once
#include<Mathf.h>
#include<Core/DataStructure/Component/Component.h>

class Shader;
class Scene;

class Light : public Component
{
public:
	virtual void ImguiWindowComponents();
	virtual void SetUniform(Shader* shader) const;
	virtual void Update(Scene* scene);

	static unsigned int NbrofPointLight;
	static unsigned int NbrofSpothLight;
	Vector4 ambiant;
	Vector4 diffuse;
	Vector4 specular;
	float SpecularStrengt;
	Light(Vector4 _ambiant , Vector4 _diffuse , Vector4 _specular , float _specularStrenght);
	Light();
	~Light();
	
private:

};

