#include "LowRenderer/RendererSystem/RendererSystem.hpp"
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "Ressources/Scene/Scene.h"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "LowRenderer/MeshRenderer/MeshRenderer.h"
#include "Ressources/Scene/Scene.h"
#include "Physics/Transform/Transform.hpp"
#include "LowRenderer/Cam/Camera.h"
#include "Core/DataStructure/Project.hpp"



void RendererSystem::Init(Scene* scene)
{
};

void RendererSystem::Awake(Scene* scene)
{

};
void RendererSystem::Start(Scene* scene)
{

};
void RendererSystem::OnDrawGizmo(Scene* scene)
{



}

void RendererSystem::FixedUpdate(Scene* scene) 
{

};
void RendererSystem::Update(Scene* scene) 
{

};
void RendererSystem::LateUpdate(Scene* scene) 
{

};

void RendererSystem::Render(Shader& shader,Scene* scene) 
{

	

	std::vector<uint8_t>* data = scene->GetComponentDataArray<MeshRenderer>();

	std::vector<MeshRenderer>* MeshRenderData = reinterpret_cast<std::vector<MeshRenderer>*>(data);

	for (uint32_t i = 0; i < MeshRenderData->size(); i++)
	{
		MeshRenderer* meshRenderer = &(*MeshRenderData)[i];
		RenderMeshRender(meshRenderer, shader, scene);
	}
};
void RendererSystem::OnResizeData(uint32_t ComponentTypeID,std::vector<uint8_t>* data) 
{

};




void RendererSystem::RenderMeshRender(const MeshRenderer* meshRender, Shader& shader, Scene* scene)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glStencilMask(0x00);

	// get Shader and bind
	shader.Use();

	glActiveTexture(GL_TEXTURE0);
	meshRender->diffuse->BindTexture();

	glActiveTexture(GL_TEXTURE1);
	meshRender->specular->BindTexture();


	Entity* entity = scene->GetEntities(meshRender->entityID);
	const Transform* transform = scene->GetComponent<Transform>(entity);
	const Matrix4X4 model = transform->World;
	const Matrix4X4 MVP = Camera::cam->GetProjectionMatrix() * Camera::cam->GetLookMatrix() * model;
	const Matrix4X4 NormalMatrix = Matrix4X4::RotationMatrix4X4(transform->rotation).Invert().Transposate();



	// Set info to shaderProgramm
	shader.SetMaterial("material", meshRender->material);
	shader.SetMatrix("model", model.GetPtr());
	shader.SetMatrix("MVP", MVP.GetPtr());
	shader.SetMatrix("NormalMatrix", NormalMatrix.GetPtr());


	// Draw The Object
	meshRender->model->Draw();

}
