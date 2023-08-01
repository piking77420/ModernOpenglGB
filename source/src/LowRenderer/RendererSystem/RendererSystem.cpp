#include "LowRenderer/RendererSystem/RendererSystem.hpp"
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "Ressources/Scene/Scene.h"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "LowRenderer/MeshRenderer/MeshRenderer.h"
#include "Ressources/Scene/Scene.h"
#include "Physics/Transform/Transform.hpp"
#include "LowRenderer/Cam/Camera.h"

void RendererSystem::Init(Scene* scene)
{
	shaderName = "NormalShader";
	shaderProgramm = Scene::ressourcesManagers->GetElement<Shader>(shaderName);

}

void RendererSystem::Render(Scene* scene)
{
	std::vector<uint8_t>* MeshRenderData = scene->m_register.ComponentsData[MeshRenderer::ComponentTypeID].second;


	for(uint32_t i = 0 ; i < MeshRenderData->size() / sizeof(MeshRenderer); i++)
	{
		size_t offset = i * sizeof(MeshRenderer);
		MeshRenderer* meshRenderer = reinterpret_cast<MeshRenderer*>(&(*MeshRenderData)[offset]);
		RenderMeshRender(meshRenderer,scene);
	}
	
}

void RendererSystem::RenderMeshRender(const MeshRenderer* meshRender, const Scene* scene)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glStencilMask(0x00);

	// get Shader and bind
	shaderProgramm->Use();

	glActiveTexture(GL_TEXTURE0);
	meshRender->diffuse->BindTexture();

	glActiveTexture(GL_TEXTURE1);
	meshRender->specular->BindTexture();


	// Set info to shaderProgramm
	shaderProgramm->SetMaterial("material", meshRender->material);

	const Entity* entity = meshRender->entity;
	const Transform* transform = scene->m_register.GetComponent<Transform>(entity);

	Matrix4X4 model = transform->World;
	Matrix4X4 MVP = scene->cam->GetProjectionMatrix() * scene->cam->GetLookMatrix() * model;
	shaderProgramm->SetMaxtrix("model", model.GetPtr());

	shaderProgramm->SetMaxtrix("MVP", MVP.GetPtr());
	shaderProgramm->SetMaxtrix("rotation", Matrix4X4::RotationMatrix4X4(transform->rotation).GetPtr());
	// Draw The Object
	meshRender->model->Draw();

	glActiveTexture(GL_TEXTURE1);
	meshRender->specular->UnBindTexture();

	glActiveTexture(GL_TEXTURE0);
	meshRender->diffuse->UnBindTexture();
}
