#pragma once
#include<Light/Light.h>
class Shader;


struct SpothLightData
{
	float constant;
	float linear;
	float quadralitic;
	float cutOff;
	float outerCutOff;
	SpothLightData(float _constant, float _linear, float _quadralitic , float _cutoff , float _outerCutOff);
	SpothLightData();
};



class SpothLight : public Light
{
public:

	void SetUniform(Shader* shader) const  override;
	void Update(Scene* scene) override;
	void ImguiWindowComponents() override;

	Vector3 LightDirection;
	Vector3 SpothDirection;
	SpothLightData spothData;

	unsigned int SpothLightID;
	SpothLight(Entity& entityAttach, const Vector4& _ambiant, const Vector4& _diffuse, const Vector4& _specular, const Vector3& _LightDirection, const Vector3& _spothDirection, const SpothLightData& _spothData) ;
	SpothLight(Entity& entityAttach);
	~SpothLight();
private:

};	

	