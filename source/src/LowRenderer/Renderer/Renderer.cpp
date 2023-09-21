#include "LowRenderer/Renderer/Renderer.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ECS/Scene/Scene.h"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "LowRenderer/MeshRenderer/MeshRenderer.h"
#include "Physics/Transform/Transform.hpp"
#include "LowRenderer/Cam/Camera.h"
#include "Core/DataStructure/Project.hpp"

	
void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{


	glViewport(0, 0, width, height);
	OpenGlRenderToImgui->ResizeFrammeBuffer(width, height);
}



void Renderer::RendereScene(Scene* scene,Shader* shader)
{
	
	std::vector<uint8_t>* data = scene->GetComponentDataArray<MeshRenderer>();

	std::vector<MeshRenderer>* MeshRenderData = reinterpret_cast<std::vector<MeshRenderer>*>(data);

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




Renderer::Renderer()
{

}

Renderer::~Renderer()
{
}


void Renderer::RenderMeshRender(const MeshRenderer* meshRender, Shader& shader, Scene* scene)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glStencilMask(0x00);

	// get Shader and bind
	shader.Use();
	


	Entity* entity = scene->GetEntities(meshRender->entityID);
	const Transform* transform = scene->GetComponent<Transform>(entity);
	const Matrix4X4 model = transform->world;
	const Matrix4X4 MVP = Camera::cam->GetProjectionMatrix() * Camera::cam->GetLookMatrix() * model;
	const Matrix4X4 NormalMatrix = Quaternion::ToRotationMatrix4X4(transform->GetRotation()).Invert().Transposate();



	// Set info to shaderProgramm
	shader.SetMatrix("model", model.GetPtr());
	shader.SetMatrix("MVP", MVP.GetPtr());
	shader.SetMatrix("NormalMatrix", NormalMatrix.GetPtr());
	shader.SetVector3("viewPos", Camera::cam->eye.GetPtr());

	
	// Set Material 
	shader.SetInt("material.diffuse",0);
	shader.SetInt("material.specular",1);
	shader.SetFloat("material.shininess", meshRender->material.shininess);
	

	// Set Diffuse Texture 
	glActiveTexture(GL_TEXTURE0);
	meshRender->material.diffuse.BindTexture();

	// Set Specular Texture 
	glActiveTexture(GL_TEXTURE1);
	meshRender->material.specular.BindTexture();
	
	// Draw The Object
	meshRender->mesh.Draw();


}

void Renderer::RenderStencil(const MeshRenderer* meshRender, const Shader& shader, Scene* scene)
{
}
