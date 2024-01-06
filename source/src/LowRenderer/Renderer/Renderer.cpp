#include "LowRenderer/Renderer/Renderer.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/ECS/Scene.h"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "LowRenderer/MeshRenderer/MeshRenderer.h"
#include "Physics/Transform/Transform.hpp"
#include "LowRenderer/Cam/Camera.h"
#include "Core/DataStructure/Project.hpp"

	



void Renderer::RendereScene(Scene* scene,Shader* shader)
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glStencilMask(0x00);

	std::vector<MeshRenderer>* MeshRenderData = scene->GetComponentDataArray<MeshRenderer>();

	for (uint32_t i = 0; i < MeshRenderData->size(); i++)
	{
		MeshRenderer* meshRenderer = &(*MeshRenderData)[i];
		RenderMeshRender(meshRenderer, *shader, scene);

		if(meshRenderer->stencil)
		{
			const Shader* stencilShader = scene->currentProject->resourcesManager.GetElement<Shader>("StencilTest");
			RenderStencil(meshRenderer, *stencilShader, scene);

		}

	}


	


}




void Renderer::RendereScene(Scene* scene)
{

}


void Renderer::RenderMeshRender(const MeshRenderer* meshRender, Shader& shader, Scene* scene)
{

	// get Shader and bind
	shader.Use();
	


	Entity* entity = scene->GetEntities(meshRender->entityID);
	const Transform* transform = scene->GetComponent<Transform>(entity);
	const Matrix4X4& model = transform->world;
	const Matrix4X4& MVP = Camera::cam->GetProjectionMatrix() * Camera::cam->GetLookMatrix() * model;
	const Matrix4X4& NormalMatrix = Quaternion::ToRotationMatrix4X4(transform->GetRotation()).Invert().Transpose() ;


	// Set info to shaderProgramm
	shader.SetMatrix("model", model.GetPtr());
	shader.SetMatrix("MVP", MVP.GetPtr());
	shader.SetMatrix("NormalMatrix", NormalMatrix.GetPtr());
	shader.SetVector3("viewPos", Camera::cam->eye.GetPtr());


	



	if (Project::shaderType == MATERIALSHADER::PHONG)
	{
		RenderPhong(meshRender, shader, scene);
	}
	else
	{
		RenderPBR(meshRender, shader, scene);

	}



}

void Renderer::RenderStencil(const MeshRenderer* meshRender, const Shader& shader, Scene* scene)
{

}

void Renderer::RenderPhong(const MeshRenderer* meshRender, Shader& shader, Scene* scene)
{

	Entity* entity = scene->GetEntities(meshRender->entityID);
	const Transform* transform = scene->GetComponent<Transform>(entity);

	// Set Material 
	shader.SetInt("material.albedo", 0);
	shader.SetFloat("material.shininess", meshRender->material.phongMaterial.shininess);
	shader.SetFloat("material.ka", meshRender->material.phongMaterial.ka);
	shader.SetFloat("material.kd", meshRender->material.phongMaterial.kd);
	shader.SetFloat("material.ks", meshRender->material.phongMaterial.ks);


	// Set Diffuse Texture 
	glActiveTexture(GL_TEXTURE0);
	meshRender->material.phongMaterial.albedo.BindTexture();


	// Draw The Object
	meshRender->mesh.Draw();

}

void Renderer::RenderPBR(const MeshRenderer* meshRender, Shader& shader, Scene* scene)
{
	Entity* entity = scene->GetEntities(meshRender->entityID);
	const Transform* transform = scene->GetComponent<Transform>(entity);
	const MaterialPBR& material = meshRender->material.pbrMaterial;

	// albedo 
	if (material.albedo.ressourceMap != nullptr)
	{
		shader.SetInt("albedoNode.AlbedoTexture", 0);
		// Set Diffuse Texture 
		glActiveTexture(GL_TEXTURE0);
		meshRender->material.pbrMaterial.albedo.ressourceMap->BindTexture();

		shader.SetBool("albedoNode.valueTexture", 1);
	}
	else
	{
		shader.SetVector3("albedoNode.color", material.albedo.coeff.GetPtr());
		shader.SetBool("albedoNode.valueTexture", 0);
	}

	// Metallic //

	if (material.metallic.ressourceMap != nullptr)
	{
		shader.SetInt("metallicNode.MetallicTexture", 1);
		shader.SetBool("metallicNode.valueTexture", 1);
		glActiveTexture(GL_TEXTURE1);
		meshRender->material.pbrMaterial.metallic.ressourceMap->BindTexture();
	}
	else
	{
		shader.SetFloat("metallicNode.metallicValue", material.metallic.coeff);
		shader.SetBool("metallicNode.valueTexture", 0);
	}

	// Rougness
	if (material.metallic.ressourceMap != nullptr)
	{
		shader.SetInt("roughnessNode.RoughnessTexture", 2);
		shader.SetBool("roughnessNode.valueTexture", 1);
		glActiveTexture(GL_TEXTURE2);
		meshRender->material.pbrMaterial.roughness.ressourceMap->BindTexture();
	}
	else
	{
		shader.SetFloat("roughnessNode.RoughnesValue", material.roughness.coeff);
		shader.SetBool("roughnessNode.valueTexture", 0);
	}


	// Occlusion
	if (material.metallic.ressourceMap != nullptr)
	{
		shader.SetInt("ambinatOcclusion.OcclusionTexture", 3);
		shader.SetBool("ambinatOcclusion.valueTexture", 1);
		glActiveTexture(GL_TEXTURE3);
		meshRender->material.pbrMaterial.ao.ressourceMap->BindTexture();
	}
	else
	{
		shader.SetFloat("ambinatOcclusion.OcclusionValue", material.ao.coeff);
		shader.SetBool("ambinatOcclusion.valueTexture", 0);
	}


	meshRender->mesh.Draw();
}
