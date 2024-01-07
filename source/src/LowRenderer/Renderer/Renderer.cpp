#include "LowRenderer/Renderer/Renderer.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/ECS/Scene.h"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "LowRenderer/MeshRenderer/MeshRenderer.h"
#include "Physics/Transform/Transform.hpp"
#include "LowRenderer/Cam/Camera.h"
#include "Core/DataStructure/Project.hpp"
#include "LowRenderer/SystemRendererSkyMap/SystemRendererSkyMap.hpp"
	



void Renderer::RendereScene(Scene* scene,Shader* shader)
{

	shader->Use();
	

	std::vector<MeshRenderer>* MeshRenderData = scene->GetComponentDataArray<MeshRenderer>();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glStencilMask(0x00);


	for (uint32_t i = 0; i < MeshRenderData->size(); i++)
	{
		MeshRenderer* meshRenderer = &(*MeshRenderData)[i];
		RenderMeshRender(meshRenderer, *shader, scene);
	}
	
	shader->UnUse();


}




void Renderer::RendereScene(Scene* scene)
{

	if (shaderType == PHONG)
	{
		m_CurrentShader = ResourcesManager::GetElement<Shader>("PHONG");
	}
	else
	{
		m_CurrentShader = ResourcesManager::GetElement<Shader>("PBR");
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glStencilMask(0x00);
	m_CurrentShader->Use();


	ComputeLight(*m_CurrentShader, scene);

	std::vector<MeshRenderer>* MeshRenderData = scene->GetComponentDataArray<MeshRenderer>();

	for (uint32_t i = 0; i < MeshRenderData->size(); i++)
	{
		MeshRenderer* meshRenderer = &(*MeshRenderData)[i];
		RenderMeshRender(meshRenderer, *m_CurrentShader, scene);

		if (meshRenderer->stencil)
		{
			const Shader* stencilShader =ResourcesManager::GetElement<Shader>("StencilTest");
			RenderStencil(meshRenderer, *stencilShader, scene);

		}
	}

	m_CurrentShader->UnUse();

}

void Renderer::ResetViewPort()
{
	if (BindedFrameBuffer == nullptr)
		return;

	BindedFrameBuffer->Bind();
	glViewport(0, 0, BindedFrameBuffer->widht, BindedFrameBuffer->height);
}


void Renderer::RenderMeshRender(const MeshRenderer* meshRender, Shader& shader, Scene* scene)
{

	// get Shader and bind
	


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


	if (Renderer::shaderType == MATERIALSHADER::PHONG)
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

	// Bind IBL //
	
	shader.SetInt("irradianceMap", 4);
	glActiveTexture(GL_TEXTURE4);
	scene->GetSystem<SystemRendererSkyMap>()->cubemap->BindIBL();
	
	shader.SetFloat("irridanceFactor", scene->GetSystem<SystemRendererSkyMap>()->irridianceFactor);

	meshRender->mesh.Draw();
}

void Renderer::ComputeLight(Shader& shader, Scene* scene)
{

	UpdateDirectionnalLights(scene->GetComponentDataArray<DirectionalLight>(), scene);

	UpdatePointLights(scene->GetComponentDataArray<PointLight>(), scene);

	UpdateSpothLights(scene->GetComponentDataArray<SpothLight>(), scene);
}

void Renderer::UpdateDirectionnalLights(std::vector<DirectionalLight>* data, Scene* scene)
{

	for (int i = 0; i < data->size(); i++)
	{
		DirectionalLight* directionalLight = (&(*data)[i]);

		RenderDirectionalLight(directionalLight, scene);

	}


}

void Renderer::UpdatePointLights(std::vector<PointLight>* data, Scene* scene)
{
	m_CurrentShader->SetInt("numberOfPointLight", (int)data->size());
	for (int i = 0; i < data->size(); i++)
	{
		PointLight* pointlight = &(*data)[i];
		Entity* entity = scene->GetEntities(pointlight->entityID);
		Transform* transformOfLight = scene->GetComponent<Transform>(entity);

		m_CurrentShader->SetVector3("pointLights[" + std::to_string(i) + "].position", static_cast<Vector3>(transformOfLight->world[3]).GetPtr());

		const Vector4 color = pointlight->lightData.color * pointlight->lightData.intensity;
		m_CurrentShader->SetVector3("pointLights[" + std::to_string(i) + "].color", color.GetPtr());

		m_CurrentShader->SetFloat("pointLights[" + std::to_string(i) + "].far_plane", pointlight->lightData.maxRange);


		//m_CurrentShader->SetInt("pointLights[" + std::to_string(i) + "].depthMapCube",10 + i);

		//glActiveTexture(GL_TEXTURE10 + i);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, pointlight->depthMap.ID);

	}
}

void Renderer::UpdateSpothLights(std::vector<SpothLight>* data, Scene* scene)
{
	for (int i = 0; i < data->size(); i++)
	{
		SpothLight* spothlight = &(*data)[i];
		Entity* entity = scene->GetEntities(spothlight->entityID);
		Transform* transformOfLight = scene->GetComponent<Transform>(entity);

		m_CurrentShader->SetVector3("spotLights[" + std::to_string(i) + "].position", static_cast<Vector3>(transformOfLight->world[3]).GetPtr());
		m_CurrentShader->SetVector3("spotLights[" + std::to_string(i) + "].direction", spothlight->direction.GetPtr());
		m_CurrentShader->SetVector3("spotLights[" + std::to_string(i) + "].color", spothlight->lightData.color.GetPtr());
		/*
		currentShader->SetFloat("spotLights[" + std::to_string(i) + "].cutOff", spothlight->cutOff);
		currentShader->SetFloat("spotLights[" + std::to_string(i) + "].outerCutOff", spothlight->outerCutOff);
		currentShader->SetFloat("spotLights[" + std::to_string(i) + "].constant", spothlight->constant);
		currentShader->SetFloat("spotLights[" + std::to_string(i) + "].quadratic", spothlight->quadratic);
		currentShader->SetInt("spotLights[" + std::to_string(i) + "].depthMapCube", 3);
		*/

	}
}

void Renderer::RenderDirectionalLight(const DirectionalLight* dirLight, Scene* scene)
{
	Entity* entity = scene->GetEntities(dirLight->entityID);
	Transform* transformOfLight = scene->GetComponent<Transform>(entity);
	Vector3 LightDirection = static_cast<Vector3>(Quaternion::ToRotationMatrix4X4(transformOfLight->GetRotation()) * Vector4(0, 1, 0, 0)).Normalize();

	const Vector4 color = dirLight->lightData.color * dirLight->lightData.intensity;

	m_CurrentShader->SetVector3("dirLight.color", color.GetPtr());
	m_CurrentShader->SetVector3("dirLight.LightDirection", LightDirection.GetPtr());
	m_CurrentShader->SetVector3("dirLight.lightPos", transformOfLight->world[3].GetPtr());
	m_CurrentShader->SetMatrix("lightSpaceMatrix", dirLight->lightData.LightSpaceMatrix.GetPtr());
	m_CurrentShader->SetInt("dirLight.FilterSize", dirLight->filterSize);
	

	m_CurrentShader->SetInt("dirLight.shadowMap", 10);
	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, dirLight->depthmap.depthMap);
}
