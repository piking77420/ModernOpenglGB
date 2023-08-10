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
	CalCulateDepthBufferDirectionnal(scene);


};
void RendererShadowSystem::OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data)
{

};
void RendererShadowSystem::OnDrawGizmo(Scene* scene)
{

}
;


void RendererShadowSystem::CalCulateDepthBufferDirectionnal(Scene* scene)
{

	Shader* depthShader = scene->currentproject->ressourcesManager.GetElement<Shader>("DepthMapShader");
	//Shader* depthShader = scene->currentproject->ressourcesManager.GetElement<Shader>("NormalShader");


	std::vector<uint8_t>* data = currentScene->GetComponentDataArray<DirectionalLight>();

	std::vector<DirectionalLight>* dataDirectionalLight = reinterpret_cast<std::vector<DirectionalLight>*>(data);

	Shader* shadowShader = scene->currentproject->ressourcesManager.GetElement<Shader>("ShadowMapping");



	for (uint32_t i = 0; i < dataDirectionalLight->size(); i++)
	{
		DirectionalLight* dirlight = &(*dataDirectionalLight)[i];
		Entity* entity = scene->GetEntities(dirlight->entityID);
		Transform* transform = currentScene->GetComponent<Transform>(entity);
		Vector3 LightDirection = static_cast<Vector3>(Matrix4X4::RotationMatrix4X4(transform->rotation) * Vector4(0, 0, -1, 0)).Normalize();

		float near_plane = 1.0f, far_plane = 7.5f;

		Matrix4X4 LightProjection = Matrix4X4::OrthoGraphicMatrix(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		Matrix4X4 LookAt = Matrix4X4::LookAt(transform->World.GetPos(), Vector3::Zero(), Vector3::Up());
		dirlight->lightData.LightSpaceMatrix = LightProjection * LookAt;

		depthShader->Use();
		depthShader->SetMatrix("lightSpaceMatrix", dirlight->lightData.LightSpaceMatrix.GetPtr());

		glViewport(0, 0, (GLuint)dirlight->lightData.depthmap.widht, (GLuint)dirlight->lightData.depthmap.height);
		dirlight->lightData.depthmap.Bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		

		//Render Scene here  
		currentScene->RenderScene(*depthShader);
		

		

		dirlight->lightData.depthmap.UnBind();

		

	}

	
	// reset viewport
	glViewport(0, 0, currentScene->currentproject->OpenGlRenderToImgui->widht, currentScene->currentproject->OpenGlRenderToImgui->height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	currentScene->currentproject->OpenGlRenderToImgui->Bind();
	
}
