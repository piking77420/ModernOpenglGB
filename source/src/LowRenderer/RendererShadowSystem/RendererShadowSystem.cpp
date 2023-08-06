#include "LowRenderer/RendererShadowSystem/RendererShadowSystem.h"
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
	depthShader = &shader;

	CalCulateDepthBufferDirectionnal();


};
void RendererShadowSystem::OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data)
{

};

void RendererShadowSystem::CalCulateDepthBufferDirectionnal()
{

	std::vector<uint8_t>* data = currentScene->GetComponentDataArray<DirectionalLight>();

	std::vector<DirectionalLight>* dataDirectionalLight = reinterpret_cast<std::vector<DirectionalLight>*>(data);

	depthShader->Use();




	for (uint32_t i = 0; i < dataDirectionalLight->size(); i++)
	{
		DirectionalLight* dirlight = &(*dataDirectionalLight)[i];
		Transform* transform = currentScene->GetComponent<Transform>(dirlight->entity);
		Vector3 LightDirection = static_cast<Vector3>(Vector4(0, 0, -1, 0) * Matrix4X4::RotationMatrix4X4(transform->rotation)).Normalize();
		//Vector3 pos, roation, scale;



		glViewport(0, 0, dirlight->lightData.depthmap.widht, dirlight->lightData.depthmap.height);
		glBindFramebuffer(GL_FRAMEBUFFER, dirlight->lightData.depthmap.FBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		Matrix4X4 LightProjection = Matrix4X4::OrthoGraphicMatrix(-10.0f, 10.0f, -10.0f, 10.0f, 1.0, 7.5f);
		Matrix4X4 LookAt = Matrix4X4::LookAt(transform->pos, LightDirection, Vector3::Up());

		dirlight->lightData.LightSpaceMatrix = LightProjection * LookAt;

		depthShader->SetMatrix("lightSpaceMatrix", dirlight->lightData.LightSpaceMatrix.GetPtr());

		//Render Scene Hero  

		if(!RendererShadowSystem::boolHasDrawBuffer)
		{
			RendererShadowSystem::boolHasDrawBuffer = true;
			currentScene->Render(*depthShader);
		}

		

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
	depthShader->UnUse();

	// reset viewport
	glViewport(0, 0, currentScene->currentproject->OpenGlRenderToImgui->widht, currentScene->currentproject->OpenGlRenderToImgui->height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	currentScene->currentproject->OpenGlRenderToImgui->Bind();

}
