#include <Light/PointLight/PointLight.h>
#include<Ressources/Shader/Shader.h>



void PointLight::SetUniform(Shader* shader) const
{
	//std::string lightindex = "[" + std::to_string(nbr) + "]";
	//std::string arrayName = "pointLights";
	//std::string arrayIndex = arrayName + lightindex;

	if(IsEnabled)
	{
		std::string Setuniform = "pointLights[" + std::to_string(pointLightID) + "]";
		shader->Use();
		shader->SetInt("nbrOfPointLight", Light::NbrofPointLight);
		shader->SetVector3(Setuniform + ".position", EntityAttachTo.transform.GetWordlPos().GetPtr());
		shader->SetVector3(Setuniform + ".ambient", ambiant.GetPtr());
		shader->SetVector3(Setuniform + ".diffuse", diffuse.GetPtr());
		shader->SetVector3(Setuniform + ".specular", specular.GetPtr());
		shader->SetFloat(Setuniform + ".constant", constant);
		shader->SetFloat(Setuniform + ".linear", linear);
		shader->SetFloat(Setuniform + ".quadratic", quadralitic);

	}

}

void PointLight::Update(Scene* scene)
{
	//sscenem_Ressources->SetLightInfoForShader(this);
}





void PointLight::ImguiWindowComponents()
{
	ImGui::Text(" ");
	ImGui::DragFloat("constant", &constant);
	ImGui::DragFloat("linear", &linear);
	ImGui::DragFloat("quadralitic", &quadralitic);
	ImGui::ColorPicker4("ambiantColor", ambiant.SetPtr());
	ImGui::ColorPicker4("DiffuseColor", diffuse.SetPtr());
	ImGui::ColorPicker4("SpecularColor", specular.SetPtr());
	ImGui::Text(" ");
}

PointLight::PointLight(Entity& entityAttach, const Vector4& _ambiant, const Vector4& _diffuse, const Vector4& _specular) : constant(1.0f) , linear(0.09f) , quadralitic(0.032f) ,Light(entityAttach)
{
	pointLightID = Light::NbrofPointLight;
	Light::NbrofPointLight++;
	m_ComponentName = "PointLight";
	ambiant = _ambiant;
	diffuse = _diffuse;
	specular = _specular;
}

PointLight::PointLight(Entity& entityAttach, const Vector4& _ambiant, const Vector4& _diffuse, const Vector4& _specular,float _constant , float _linear , float _quadralitic) :  Light(entityAttach) 
{
	pointLightID = Light::NbrofPointLight;
	Light::NbrofPointLight++;
	m_ComponentName = "PointLight";
	ambiant = _ambiant;
	diffuse = _diffuse;
	specular = _specular;
	constant = _constant;
	linear = _linear;
	quadralitic = _quadralitic;
}

PointLight::PointLight(Entity& entityAttach) : constant(1.0f), linear(0.09f), quadralitic(0.032f) , Light(entityAttach)
{
	pointLightID = Light::NbrofPointLight;
	Light::NbrofPointLight++;
	m_ComponentName = "PointLight";
	ambiant = Vector4::One;
	diffuse = Vector4::One;
	specular = Vector4::One;
}

PointLight::~PointLight()
{
	Light::NbrofPointLight--;
}
