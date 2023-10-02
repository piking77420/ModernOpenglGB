#include "LowRenderer/RendererLightSystem/RendererLightSystem.hpp"
#include<vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Debug/Debug.h"
#include "LowRenderer/Light/DirectionalLight/DirectionalLight.hpp"
#include "LowRenderer/Light/SpothLight/SpothLight.hpp"
#include "LowRenderer/Light/PointLight/PointLight.hpp"
#include "Core/ECS/Scene.h"
#include "Physics/Transform/Transform.hpp"
#include "Core/DataStructure/Project.hpp"



void RendererLightSystem::OnDrawGizmo(Scene* scene)
{



}

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
	






	currentShader->Use();


	UpdateDirectionnalLights(scene->GetComponentDataArray<DirectionalLight>(), scene);

	UpdatePointLights(scene->GetComponentDataArray<PointLight>(), scene);

	UpdateSpothLights(scene->GetComponentDataArray<SpothLight>(), scene);

	currentShader->UnUse();

};
void RendererLightSystem::OnResizeData(uint32_t ComponentTypeID,std::vector<uint8_t>* data)
{

};










void RendererLightSystem::UpdateDirectionnalLights(std::vector<DirectionalLight>* data, Scene* scene)
{
	if(data->size() > sizeof(DirectionalLight))
	{
		LOG("There Is One more than one DirectionnalLight", STATELOG::CRITICALERROR);
	}


	for (size_t i = 0; i < data->size(); i++)
	{
		DirectionalLight* directionalLight = (&(*data)[i]);

		if (!directionalLight->isEnable)
			continue;

		RenderDirectionalLight(directionalLight, scene);

	}
}

void RendererLightSystem::UpdatePointLights(std::vector<PointLight>* data, Scene* scene)
{
	

	currentShader->SetInt("numberOfPointLight", data->size());
	for (size_t i = 0; i < data->size(); i++)
	{
		PointLight* pointlight = &(*data)[i];
		Entity* entity = scene->GetEntities(pointlight->entityID);
		Transform* transformOfLight = scene->GetComponent<Transform>(entity);

		currentShader->SetVector3("pointLights[" + std::to_string(i) + "].position", transformOfLight->world.GetPos().GetPtr());
		currentShader->SetVector3("pointLights[" + std::to_string(i) + "].color", pointlight->lightData.color.GetPtr());
		currentShader->SetFloat("pointLights[" + std::to_string(i) + "].constant", pointlight->constant);
		currentShader->SetFloat("pointLights[" + std::to_string(i) + "].quadratic", pointlight->quadratic);
		currentShader->SetFloat("pointLights[" + std::to_string(i) + "].far_plane", pointlight->lightData.maxRange);


		currentShader->SetInt("pointLights[" + std::to_string(i) + "].depthMapCube",10 + i );

		glActiveTexture(GL_TEXTURE10 + i );
		glBindTexture(GL_TEXTURE_CUBE_MAP, pointlight->depthMap.ID);

	}

}

void RendererLightSystem::UpdateSpothLights(std::vector<SpothLight>* data, Scene* scene)
{



	for (size_t i = 0; i < data->size(); i++)
	{
		SpothLight* spothlight = &(*data)[i];
		Entity* entity = scene->GetEntities(spothlight->entityID);
		Transform* transformOfLight = scene->GetComponent<Transform>(entity);

		currentShader->SetVector3("spotLights[" + std::to_string(i) + "].position", transformOfLight->world.GetPos().GetPtr());
		currentShader->SetVector3("spotLights[" + std::to_string(i) + "].direction", spothlight->direction.GetPtr());
		currentShader->SetVector3("spotLights[" + std::to_string(i) + "].color", spothlight->lightData.color.GetPtr());
		currentShader->SetFloat("spotLights[" + std::to_string(i) + "].cutOff", spothlight->cutOff);
		currentShader->SetFloat("spotLights[" + std::to_string(i) + "].outerCutOff", spothlight->outerCutOff);
		currentShader->SetFloat("spotLights[" + std::to_string(i) + "].constant", spothlight->constant);
		currentShader->SetFloat("spotLights[" + std::to_string(i) + "].quadratic", spothlight->quadratic);
		currentShader->SetInt("spotLights[" + std::to_string(i) + "].depthMapCube", 3);
		
	
	}

}




void RendererLightSystem::RenderDirectionalLight(const DirectionalLight* dirLight, Scene* scene)
{
	Entity* entity = scene->GetEntities(dirLight->entityID);
	Transform* transformOfLight = scene->GetComponent<Transform>(entity);
	Vector3 LightDirection = static_cast<Vector3>(Quaternion::ToRotationMatrix4X4(transformOfLight->GetRotation()) * Vector4(0,1,0,0) ).Normalize();
	
	currentShader->SetVector3("dirLight.color", dirLight->lightData.color.GetPtr());
	
	currentShader->SetVector3("dirLight.LightDirection", LightDirection.GetPtr());

	currentShader->SetVector3("dirLight.lightPos", transformOfLight->world.GetPos().GetPtr());
	currentShader->SetMatrix("lightSpaceMatrix", dirLight->lightData.LightSpaceMatrix.GetPtr());


	currentShader->SetInt("dirLight.shadowMap", 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, dirLight->depthmap.depthMap);


}

