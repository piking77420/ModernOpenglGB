#include "LowRenderer/SystemRendererSkyMap/SystemRendererSkyMap.hpp"
#include "ECS/Scene.h"
#include "Physics/Transform/Transform.hpp"
#include "Core/DataStructure/Project.hpp"
#include "Ressources/SkyBox/SkyBox.h"


void SystemRendererSkyMap::OnDrawGizmo(Scene* scene)
{



}


void SystemRendererSkyMap::Init(Scene* scene)
{
	

	

};

void SystemRendererSkyMap::Awake(Scene* scene)
{

};
void SystemRendererSkyMap::Start(Scene* scene)
{

};


void SystemRendererSkyMap::FixedUpdate(Scene* scene)
{

};
void SystemRendererSkyMap::Update(Scene* scene)
{

};
void SystemRendererSkyMap::LateUpdate(Scene* scene)
{

};

void SystemRendererSkyMap::Render(Shader& shader,Scene* scene)
{
	
	SkyBox skybox;

	if(skybox.cubemap == nullptr)
	{
		skybox.cubemap = scene->currentProject->resourcesManager.GetElement<CubeMaps>("SkySkybox");
	}



	shaderProgram = scene->currentProject->resourcesManager.GetElement<Shader>("SkyBoxShader");
	shaderProgram->Use();
	shaderProgram->SetInt("skybox", 30);




	shaderProgram->Use();
	shaderProgram->SetMatrix("VP", (Camera::cam->GetProjectionMatrix() * Camera::cam->GetLookMatrix()).GetPtr());
	// TO DO RESERVE FOR EACH TEXTRURE A SLOT 
	glActiveTexture(GL_TEXTURE30);
	skybox.cubemap->BindCubeMap();
	glDepthFunc(GL_LEQUAL);
	glBindVertexArray(skybox.cubemap->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
	skybox.cubemap->UnBindCubeMap();



	shaderProgram->UnUse();
};
void SystemRendererSkyMap::OnResizeData(uint32_t ComponentTypeID,std::vector<uint8_t>* data)
{

};