#include "LowRenderer/RendererShadowSystem/RendererShadowSystem.h"
#include<vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Debug/Debug.h"
#include "LowRenderer/Light/DirectionalLight/DirectionalLight.hpp"
#include "LowRenderer/Light/SpothLight/SpothLight.hpp"
#include "LowRenderer/Light/PointLight/PointLight.hpp"
#include "ECS/Scene/Scene.h"
#include "Physics/Transform/Transform.hpp"
#include "Core/DataStructure/Project.hpp"
#include "LowRenderer/Light/PointLight/PointLight.hpp"
#include "Core/Debug/AssertClass.h"
#include "LowRenderer/Light/SpothLight/SpothLight.hpp"
#include "App/App.h"
void RendererShadowSystem::Init(Scene* scene)
{

};

void RendererShadowSystem::Awake(Scene* scene)
{

};
void RendererShadowSystem::Start(Scene* scene)
{

};


void RendererShadowSystem::FixedUpdate(Scene* scene)
{
	// Check If The nbr Of PointLight is Less or equal to The Shader PointLight Array here 100

#ifdef _DEBUG

	std::vector<PointLight>* pointLightData = reinterpret_cast<std::vector<PointLight>*>(scene->GetComponentDataArray<PointLight>());
	Debug::Assert->Assertion(pointLightData->size() < 10);

	std::vector<SpothLight>* spothLightData = reinterpret_cast<std::vector<SpothLight>*>(scene->GetComponentDataArray<SpothLight>());
	Debug::Assert->Assertion(spothLightData->size() < 100);

#endif 


};
void RendererShadowSystem::Update(Scene* scene)
{

};
void RendererShadowSystem::LateUpdate(Scene* scene)
{
	
};

void RendererShadowSystem::Render(Shader& shader, Scene* scene)
{
	currentScene = scene;
	CalCulateDepthBufferDirectionnal(scene);


};
void RendererShadowSystem::OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data)
{

};
void RendererShadowSystem::OnDrawGizmo(Scene* scene)
{

};



void RendererShadowSystem::CalCulateDepthBufferDirectionnal(Scene* scene)
{

	Shader* depthShader = scene->currentProject->resourcesManager.GetElement<Shader>("DepthMapShader");
	std::vector<uint8_t>* data = currentScene->GetComponentDataArray<DirectionalLight>();
	std::vector<DirectionalLight>* dataDirectionalLight = reinterpret_cast<std::vector<DirectionalLight>*>(data);



	for (uint32_t i = 0; i < dataDirectionalLight->size(); i++)
	{
		DirectionalLight* dirlight = &(*dataDirectionalLight)[i];
		Entity* entity = scene->GetEntities(dirlight->entityID);
		Transform* transform = currentScene->GetComponent<Transform>(entity);
		Vector3 LightDirection = static_cast<Vector3>(Quaternion::ToRotationMatrix4X4(transform->GetRotation()) * Vector4(0, 1,0, 0)).Normalize();

		float size = dirlight->lightData.size;
		Matrix4X4 LightProjection = Matrix4X4::OrthoGraphicMatrix(-dirlight->lightData.size, size, -size, size, dirlight->lightData.minimumRange, dirlight->lightData.maxRange);

		Matrix4X4 LookAt = Matrix4X4::LookAt(transform->world.GetPos(), LightDirection, Vector3::Up());
		dirlight->lightData.LightSpaceMatrix = LightProjection * LookAt;

		depthShader->Use();
		depthShader->SetMatrix("lightSpaceMatrix", dirlight->lightData.LightSpaceMatrix.GetPtr());

		glViewport(0, 0, (GLuint)dirlight->depthmap.widht, (GLuint)dirlight->depthmap.height);
		dirlight->depthmap.Bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		
		//Render Scene here  
		glCullFace(GL_FRONT);
		currentScene->RenderScene(*depthShader);
		glCullFace(GL_BACK);


		dirlight->depthmap.UnBind();

		

	}


	ResetViewPort();
	
}



void RendererShadowSystem::CalCulateDepthBufferSpothLight(Scene* scene)
{
	/*
	Shader* depthShader = scene->currentproject->ressourcesManager.GetElement<Shader>("DepthMapShader");
	std::vector<SpothLight>* dataDirectionalLight = reinterpret_cast<std::vector<SpothLight>*>(currentScene->GetComponentDataArray<SpothLight>());



	for (uint32_t i = 0; i < dataDirectionalLight->size(); i++)
	{
		SpothLight* spothLight= &(*dataDirectionalLight)[i];
		Entity* entity = scene->GetEntities(spothLight->entityID);
		Transform* transform = currentScene->GetComponent<Transform>(entity);
		Vector3 LightDirection = static_cast<Vector3>(Matrix4X4::RotationMatrix4X4(transform->rotation) * Vector4(0, 1, 0, 0)).Normalize();

		float size = spothLight->lightData.size;
		Matrix4X4 LightProjection = Matrix4X4::OrthoGraphicMatrix(-spothLight->lightData.size, size, -size, size, spothLight->lightData.minimumRange, spothLight->lightData.maxRange);

		Matrix4X4 LookAt = Matrix4X4::LookAt(transform->World.GetPos(), LightDirection, Vector3::Up());
		spothLight->lightData.LightSpaceMatrix = LightProjection * LookAt;

		depthShader->Use();
		depthShader->SetMatrix("lightSpaceMatrix", spothLight->lightData.LightSpaceMatrix.GetPtr());

		glViewport(0, 0, (GLuint)spothLight->depthmap.widht, (GLuint)spothLight->depthmap.height);
		spothLight->depthmap.Bind();
		glClear(GL_DEPTH_BUFFER_BIT);

		//Render Scene here  
		glCullFace(GL_FRONT);
		currentScene->RenderScene(*depthShader);
		glCullFace(GL_BACK);


		spothLight->depthmap.UnBind();



	}*/
}
void RendererShadowSystem::ResetViewPort() const
{
	// reset viewport
	glViewport(0, 0, currentScene->renderer.OpenGlRenderToImgui->widht, currentScene->renderer.OpenGlRenderToImgui->height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	currentScene->renderer.OpenGlRenderToImgui->Bind();
	//glViewport(0, 0, windowWidth, windowHeight);

}
void RendererShadowSystem::CalCulateDepthBufferPointLight(Scene* scene)
{
	
	Shader* depthShader = scene->currentProject->resourcesManager.GetElement<Shader>("DepthMapShaderPointLight");
	std::vector<PointLight>* dataDirectionalLight = reinterpret_cast<std::vector<PointLight>*>(currentScene->GetComponentDataArray<PointLight>());



	for (uint32_t i = 0; i < dataDirectionalLight->size(); i++)
	{
		PointLight* pointLight = &(*dataDirectionalLight)[i];
		Entity* entity = scene->GetEntities(pointLight->entityID);
		Transform* transform = currentScene->GetComponent<Transform>(entity);

		float shadowWidht = pointLight->depthMap.width;
		float shadowHeight = pointLight->depthMap.height;

		Vector3 lightPos = transform->world.GetPos();
		Matrix4X4 shadowProj = Matrix4X4::PerspectiveMatrix(Math::Deg2Rad * 90.f, (float)shadowWidht / (float)shadowHeight, pointLight->lightData.minimumRange, pointLight->lightData.maxRange);
		std::array<Matrix4X4, 6> shadowTransforms;


		pointLight->shadowTransforms[0] = shadowProj * Matrix4X4::LookAt(lightPos, lightPos + Vector3::Right(), Vector3::Down());
		pointLight->shadowTransforms[1] = shadowProj * Matrix4X4::LookAt(lightPos, lightPos + Vector3::Left(), Vector3::Down());
		pointLight->shadowTransforms[2] = shadowProj * Matrix4X4::LookAt(lightPos, lightPos + Vector3::Up(), Vector3::Forward());
		pointLight->shadowTransforms[3] = shadowProj * Matrix4X4::LookAt(lightPos, lightPos + Vector3::Down(), Vector3::BackForward());
		pointLight->shadowTransforms[4] = shadowProj * Matrix4X4::LookAt(lightPos, lightPos + Vector3::Forward(), Vector3::Down());
		pointLight->shadowTransforms[5] = shadowProj * Matrix4X4::LookAt(lightPos, lightPos + Vector3::BackForward(), Vector3::Down());





		depthShader->Use();
	
		glViewport(0, 0, shadowWidht, shadowHeight);
		glBindFramebuffer(GL_FRAMEBUFFER, pointLight->depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		//Render Scene here  
		for (unsigned int i = 0; i < 6; ++i)
		{
			depthShader->SetMatrix("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i].GetPtr());
			depthShader->SetFloat("far_plane", pointLight->lightData.maxRange);
			depthShader->SetVector3("lightPos", lightPos.GetPtr());
		}

		glCullFace(GL_FRONT);
		currentScene->RenderScene(*depthShader);
		glCullFace(GL_BACK);


		glBindFramebuffer(GL_FRAMEBUFFER,0);



	}
	ResetViewPort();

}