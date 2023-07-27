#include <Light/SpothLight/SpothLight.h>
#include<Ressources/Shader/Shader.h>
#include"Mathf.h"
#include"Vector4.h"




void SpothLight::SetUniform(Shader* shader) const
{

	std::string setuniform = "spotLight[" + std::to_string(SpothLightID) + "]";
	if(IsEnabled)
	{
		shader->Use();
		shader->SetInt("nbrOfSpothLightLight", Light::NbrofSpothLight);
		shader->SetVector3(setuniform +".position", EntityAttachTo->transform.GetWordlPos().GetPtr());
		shader->SetVector3(setuniform +".direction", SpothDirection.GetPtr());
		shader->SetVector3(setuniform + ".ambient", &ambiant.x);
		shader->SetVector3(setuniform + ".diffuse", diffuse.GetPtr());
		shader->SetVector3(setuniform + ".specular", specular.GetPtr());

		shader->SetFloat(setuniform+".constant", spothData.constant);
		shader->SetFloat(setuniform+".linear", spothData.linear);
		shader->SetFloat(setuniform+".quadratic", spothData.quadralitic);
		shader->SetFloat(setuniform+".cutOff", spothData.cutOff);
		shader->SetFloat(setuniform+".outerCutOff", spothData.outerCutOff);

	}
}

void SpothLight::Update(Scene* scene)
{
}

void SpothLight::ImguiWindowComponents()
{
	ImGui::Text(" ");
	ImGui::SliderFloat3("LightDirection", LightDirection.SetPtr(), -1, 1);
	ImGui::DragFloat("constant",&spothData.constant);
	ImGui::DragFloat("linear", &spothData.linear);
	ImGui::DragFloat("quadralitic", &spothData.quadralitic);
	ImGui::SliderAngle("cutOff", &spothData.cutOff);
	ImGui::SliderAngle("outerCutOff", &spothData.outerCutOff);

		
	
	ImGui::ColorPicker4("ambiantColor", &ambiant.x);
	ImGui::ColorPicker4("DiffuseColor", &diffuse.x);
	ImGui::ColorPicker4("SpecularColor", &specular.x);
	ImGui::Text(" ");
}

SpothLight::SpothLight( const Vector4& _ambiant, const Vector4& _diffuse, const Vector4& _specular, const Vector3& _LightDirection, const Vector3& _spothDirection, const SpothLightData& _spothData) 
{
	Light::NbrofSpothLight++;
	m_ComponentName = "Spothlight";
	LightDirection = _LightDirection;
	SpothDirection = _spothDirection;

	ambiant = _ambiant;
	diffuse = _diffuse;
	specular = _specular;

	spothData = _spothData;
	
}

SpothLight::SpothLight() 
{
	SpothLightID = Light::NbrofSpothLight;
	Light::NbrofSpothLight++;
	m_ComponentName = "Spothlight";
	SpecularStrengt = 32;
	LightDirection = Vector3::Forward();
	SpothDirection = Vector3::Forward();

	ambiant = Vector4::Zero();
	diffuse = Vector4::One();
	specular = Vector4::One();

}


SpothLight::~SpothLight()
{
	Light::NbrofSpothLight--;
}

SpothLightData::SpothLightData(float _constant, float _linear, float _quadralitic, float _cutoff, float _outerCutOff)
{

	constant = _constant;
	linear = _linear;
	quadralitic = _quadralitic;
	cutOff = Math::DegreesToRadians(_cutoff);
	outerCutOff = Math::DegreesToRadians(_outerCutOff);
	Light::NbrofSpothLight++;
}

SpothLightData::SpothLightData()
{
	constant = 1.f;
	linear = 0.09f;
	quadralitic = 0.032f;
	cutOff = Math::DegreesToRadians(12.5f);
	outerCutOff = Math::DegreesToRadians(15.f);
}
