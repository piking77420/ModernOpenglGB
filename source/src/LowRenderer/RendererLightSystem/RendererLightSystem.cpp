#include<vector>
#include "LowRenderer/RendererLightSystem/RendererLightSystem.hpp"
#include "Core/Debug/Debug.h"
#include "LowRenderer/Light/DirectionalLight/DirectionalLight.hpp"
#include "LowRenderer/Light/SpothLight/SpothLight.hpp"
#include "LowRenderer/Light/PointLight/PointLight.hpp"
#include "Ressources/Scene/Scene.h"
#include "Physics/Transform/Transform.hpp"


void RendererLightSystem::Init(Scene* scene)
{
	shaderProgramm = Scene::ressourcesManagers->GetElement<Shader>(shaderName);
}

void RendererLightSystem::Render(Scene* scene)
{
	if(!shaderProgramm)
	{
		LOG("ShaderProgramm Is Nullptr ", STATELOG::CRITICALERROR);
	}
	shaderProgramm->Use();

	UpdateDirectionnalLights(scene->m_register.ComponentsData[DirectionalLight::ComponentTypeID].second, scene);

	UpdatePointLights(scene->m_register.ComponentsData[PointLight::ComponentTypeID].second, scene);

	UpdateSpothLights(scene->m_register.ComponentsData[SpothLight::ComponentTypeID].second, scene);

	shaderProgramm->UnUse();

}

void RendererLightSystem::UpdateDirectionnalLights(std::vector<uint8_t>* data, Scene* scene)
{
	if(data->size() > sizeof(DirectionalLight))
	{
		LOG("There Is One more than one DirectionnalLight", STATELOG::CRITICALERROR);
	}


	for (size_t i = 0; i < data->size() / sizeof(DirectionalLight); i++)
	{
		size_t offset = i * sizeof(DirectionalLight);
		DirectionalLight* directionalLight = reinterpret_cast<DirectionalLight*>(&(*data)[offset]);
		if (!directionalLight->IsEnable)
			continue;

		RenderDirectionalLight(directionalLight, scene);

	}
}

void RendererLightSystem::UpdatePointLights(std::vector<uint8_t>* data, Scene* scene)
{
	for (size_t i = 0; i < data->size() / sizeof(PointLight); i++)
	{
		size_t offset = i * sizeof(PointLight);
		PointLight* pointLight = reinterpret_cast<PointLight*>(&(*data)[offset]);
		if (!pointLight->IsEnable)
			continue;

		RenderPointLight(pointLight, scene);

	}
}

void RendererLightSystem::UpdateSpothLights(std::vector<uint8_t>* data, Scene* scene)
{

	for (size_t i = 0; i < data->size() / sizeof(SpothLight); i++)
	{
		size_t offset = i * sizeof(SpothLight);
		SpothLight* spothLight = reinterpret_cast<SpothLight*>(&(*data)[offset]);
		if (!spothLight->IsEnable)
			continue;

		RenderSpothLight(spothLight, scene);

	}

}


// Render Light  // 

void RendererLightSystem::RenderDirectionalLight(const DirectionalLight* dirLight, Scene* scene)
{
	Transform* transformOfLight = scene->m_register.GetComponent<Transform>(dirLight->entity);


	shaderProgramm->SetVector3("lightPos", transformOfLight->World.GetPos().GetPtr());
	shaderProgramm->SetVector3("dirLight.direction", dirLight->direction.GetPtr());
	shaderProgramm->SetVector3("dirLight.ambient", dirLight->lightData.ambiantColor.GetPtr());
	shaderProgramm->SetVector3("dirLight.diffuse", dirLight->lightData.diffuseColor.GetPtr());
	shaderProgramm->SetVector3("dirLight.specular", dirLight->lightData.specularColor.GetPtr());
	//shader->SetMaxtrix("lightSpaceMatrix", GetLightSpaceMatrix().GetPtr());
}

void RendererLightSystem::RenderPointLight(const PointLight* dirLight, Scene* scene)
{
}

void RendererLightSystem::RenderSpothLight(const SpothLight* dirLight, Scene* scene)
{
}