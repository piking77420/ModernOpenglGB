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


void RendererLightSystem::Render(Scene* scene)
{
	/*
	currentShader = &shader;

	currentShader->Use();


	UpdateDirectionnalLights(scene->GetComponentDataArray<DirectionalLight>(), scene);

	UpdatePointLights(scene->GetComponentDataArray<PointLight>(), scene);

	UpdateSpothLights(scene->GetComponentDataArray<SpothLight>(), scene);

	currentShader->UnUse();
	*/
};

void RendererLightSystem::UpdateDirectionnalLights(std::vector<DirectionalLight>* data, Scene* scene)
{

	for (int i = 0; i < data->size(); i++)
	{
		DirectionalLight* directionalLight = (&(*data)[i]);
	
		RenderDirectionalLight(directionalLight, scene);

	}
}

void RendererLightSystem::UpdatePointLights(std::vector<PointLight>* data, Scene* scene)
{
	

	currentShader->SetInt("numberOfPointLight", (int)data->size());
	for (int i = 0; i < data->size(); i++)
	{
		PointLight* pointlight = &(*data)[i];
		Entity* entity = scene->GetEntities(pointlight->entityID);
		Transform* transformOfLight = scene->GetComponent<Transform>(entity);

		currentShader->SetVector3("pointLights[" + std::to_string(i) + "].position", static_cast<Vector3>(transformOfLight->world[3]).GetPtr());

		const Vector4 color = pointlight->lightData.color * pointlight->lightData.intensity;
		currentShader->SetVector3("pointLights[" + std::to_string(i) + "].color", color.GetPtr());

		currentShader->SetFloat("pointLights[" + std::to_string(i) + "].far_plane", pointlight->lightData.maxRange);


		//currentShader->SetInt("pointLights[" + std::to_string(i) + "].depthMapCube",10 + i);

		//glActiveTexture(GL_TEXTURE10 + i);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, pointlight->depthMap.ID);

	}

}

void RendererLightSystem::UpdateSpothLights(std::vector<SpothLight>* data, Scene* scene)
{

	for (int i = 0; i < data->size(); i++)
	{
		SpothLight* spothlight = &(*data)[i];
		Entity* entity = scene->GetEntities(spothlight->entityID);
		Transform* transformOfLight = scene->GetComponent<Transform>(entity);

		currentShader->SetVector3("spotLights[" + std::to_string(i) + "].position", static_cast<Vector3>(transformOfLight->world[3]).GetPtr());
		currentShader->SetVector3("spotLights[" + std::to_string(i) + "].direction", spothlight->direction.GetPtr());
		currentShader->SetVector3("spotLights[" + std::to_string(i) + "].color", spothlight->lightData.color.GetPtr());
		/*
		currentShader->SetFloat("spotLights[" + std::to_string(i) + "].cutOff", spothlight->cutOff);
		currentShader->SetFloat("spotLights[" + std::to_string(i) + "].outerCutOff", spothlight->outerCutOff);
		currentShader->SetFloat("spotLights[" + std::to_string(i) + "].constant", spothlight->constant);
		currentShader->SetFloat("spotLights[" + std::to_string(i) + "].quadratic", spothlight->quadratic);
		currentShader->SetInt("spotLights[" + std::to_string(i) + "].depthMapCube", 3);
		*/
	
	}

}




void RendererLightSystem::RenderDirectionalLight(const DirectionalLight* dirLight, Scene* scene)
{
		Entity* entity = scene->GetEntities(dirLight->entityID);
		Transform* transformOfLight = scene->GetComponent<Transform>(entity);
		Vector3 LightDirection = static_cast<Vector3>(Quaternion::ToRotationMatrix4X4(transformOfLight->GetRotation()) * Vector4(0,1,0,0) ).Normalize();
	
		const Vector4 color = dirLight->lightData.color * dirLight->lightData.intensity;

		currentShader->SetVector3("dirLight.color", color.GetPtr());

		currentShader->SetVector3("dirLight.LightDirection", LightDirection.GetPtr());

		currentShader->SetVector3("dirLight.lightPos", transformOfLight->world[3].GetPtr());
		currentShader->SetMatrix("lightSpaceMatrix", dirLight->lightData.LightSpaceMatrix.GetPtr());



		/*
		currentShader->SetInt("dirLight.shadowMap", 2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, dirLight->depthmap.depthMap);

		*/

}

