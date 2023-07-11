#include <Light/DirectionalLight/DirectionalLight.h>
#include<Ressources/Shader/Shader.h>
#include"Vector4.h"



/*
Matrix4X4& DirectionalLight::SetLookAtMatrix()
{
	Matrix4X4 look = Matrix4X4().LookAt(EntityAttachTo->transform.GetWordlPos(), Vector3::Zero, Vector3(0.0, 1.0, 0.0));

	Matrix4X4 ortho = Matrix4X4().OrthoGraphicMatrix(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

	return m_LightViewMatrix;
}*/

const Matrix4X4& DirectionalLight::GetLookAtMatrix() const
{
	float near_plane = 1.0f, far_plane = 7.5f;

	Matrix4X4 look = Matrix4X4().LookAt(EntityAttachTo->transform.GetWordlPos(), Vector3::Zero, Vector3(0.0, 1.0, 0.0));

	Matrix4X4 ortho = Matrix4X4().OrthoGraphicMatrix(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

	return ortho * look;
}

void DirectionalLight::ImguiWindowComponents()
{

	ImGui::Text(" ");
	ImGui::DragFloat3("LightDirection", &Direction.x, -1, 1);
	ImGui::ColorPicker4("ambiantColor", ambiant.SetPtr());
	ImGui::ColorPicker4("diffuseLightColor", diffuse.SetPtr());
	ImGui::ColorPicker4("SpecularColor", specular.SetPtr());
	ImGui::Text(" ");
}

void DirectionalLight::SetUniform(Shader* shader) const
{
	if(IsEnabled)
	{


		shader->Use();

		shader->SetVector3("lightPos", EntityAttachTo->transform.GetWordlPos().GetPtr());

		shader->SetVector3("dirLight.direction",Direction.GetPtr());
		shader->SetVector3("dirLight.ambient", ambiant.GetPtr());
		shader->SetVector3("dirLight.diffuse", diffuse.GetPtr());
		shader->SetVector3("dirLight.specular", specular.GetPtr());
		shader->SetMaxtrix("lightSpaceMatrix", GetLookAtMatrix().GetPtr());

	}
}

void DirectionalLight::Update(Scene* scene)
{
}

DirectionalLight::DirectionalLight(const Vector4& _ambiant, const Vector4& _diffuse, const Vector4& _specular, const Vector4& _Direction) 
{
	m_ComponentName = "DirectionnalLight";
	ambiant = _ambiant;
	diffuse = _diffuse;
	specular = _specular;
	Direction = _Direction;
}

DirectionalLight::DirectionalLight() 
{
	m_ComponentName = "DirectionnalLight";

	ambiant = Vector4::One;
	diffuse = Vector4::One;
	specular = Vector4::One;
	Direction = Vector3::Forward;
}


DirectionalLight::~DirectionalLight()
{
}
