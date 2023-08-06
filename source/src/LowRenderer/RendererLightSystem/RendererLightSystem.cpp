#include "LowRenderer/RendererLightSystem/RendererLightSystem.hpp"
#include<vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Debug/Debug.h"
#include "LowRenderer/Light/DirectionalLight/DirectionalLight.hpp"
#include "LowRenderer/Light/SpothLight/SpothLight.hpp"
#include "LowRenderer/Light/PointLight/PointLight.hpp"
#include "Ressources/Scene/Scene.h"
#include "Physics/Transform/Transform.hpp"
#include "Core/DataStructure/Project.hpp"




void RendererLightSystem::Init(Scene* scene)
{
};

void RendererLightSystem::Awake(Scene* scene)
{

};
void RendererLightSystem::Start(Scene* scene)
{

};


void RendererLightSystem::FixedUpdate(Scene* scene)
{

};
void RendererLightSystem::Update(Scene* scene)
{

};
void RendererLightSystem::LateUpdate(Scene* scene)
{

};

void RendererLightSystem::Render(Shader& shader, Scene* scene)
{
	currentShader = &shader;
	// Calulate Depthmap
	







	currentShader->Use();

	UpdateDirectionnalLights(scene->GetComponentDataArray<DirectionalLight>(), scene);

	UpdatePointLights(scene->GetComponentDataArray<PointLight>(), scene);

	UpdateSpothLights(scene->GetComponentDataArray<SpothLight>(), scene);

	currentShader->UnUse();

};
void RendererLightSystem::OnResizeData(uint32_t ComponentTypeID,std::vector<uint8_t>* data)
{

};










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




void RendererLightSystem::RenderDirectionalLight(const DirectionalLight* dirLight, Scene* scene)
{
	Transform* transformOfLight = scene->GetComponent<Transform>(dirLight->entity);
	Vector3 LightDirection = static_cast<Vector3>( Vector4(0,0,-1,0) * Matrix4X4::RotationMatrix4X4(transformOfLight->rotation)).Normalize();

	currentShader->SetVector3("lightPos", transformOfLight->World.GetPos().GetPtr());
	currentShader->SetMatrix("lightSpaceMatrix", dirLight->lightData.LightSpaceMatrix.GetPtr());
	currentShader->SetVector3("dirLight.direction", LightDirection.GetPtr());
	currentShader->SetVector3("dirLight.ambient", dirLight->lightData.ambiantColor.GetPtr());
	currentShader->SetVector3("dirLight.diffuse", dirLight->lightData.diffuseColor.GetPtr());
	currentShader->SetVector3("dirLight.specular", dirLight->lightData.specularColor.GetPtr());

	currentShader->SetInt("shadowMap", 29);
	glActiveTexture(GL_TEXTURE29);
	glBindTexture(GL_TEXTURE_2D, dirLight->lightData.depthmap.framebufferTexture);


	//shader->SetMaxtrix("lightSpaceMatrix", GetLightSpaceMatrix().GetPtr());
}

void RendererLightSystem::RenderPointLight(const PointLight* dirLight, Scene* scene)
{
}

void RendererLightSystem::RenderSpothLight(const SpothLight* dirLight, Scene* scene)
{
}
