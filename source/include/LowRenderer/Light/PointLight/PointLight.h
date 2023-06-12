#pragma once
#include<Debug/LogClass.h>
#include<LowRenderer/Light/Light.h>


class Shader;


class PointLight : public Light
{
public:

	void SetUniform(Shader* shader) const override;
	void Update(Scene* appData) override;
	void ImguiWindowComponents() override;

	unsigned int pointLightID;
	float constant;
	float linear;
	float quadralitic;
	
	PointLight(const Vector4& _ambiant, const Vector4& _diffuse, const Vector4& _specular);
	PointLight(const Vector4& _ambiant, const Vector4& _diffuse, const Vector4& _specular, float _constant, float _linear, float _quadralitic);
	PointLight();
	~PointLight();
private:

};

