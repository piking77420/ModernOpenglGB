#include "LowRenderer/SystemRendererSkyMap/SystemRendererSkyMap.hpp"
#include "Ressources/Scene/Scene.h"
#include "Physics/Transform/Transform.hpp"
#include "Core/DataStructure/Project.hpp"
#include "Ressources/SkyBox/SkyBox.h"



void SystemRendererSkyMap::OnDrawGizmo(Scene* scene)
{



}


void SystemRendererSkyMap::Init(Scene* scene)
{
	

	skybox = scene->currentproject->ressourcesManager.GetElement<SkyBox>("SkySkybox");
	shaderProgram = scene->currentproject->ressourcesManager.GetElement<Shader>("SkyBoxShader");
	shaderProgram->Use();
	shaderProgram->SetInt("skybox", 30);

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

	shaderProgram->Use();

	// TO DO RESERVE FOR EACH TEXTRURE A SLOT 
	glActiveTexture(GL_TEXTURE30);
	skybox->cubemap.BindCubeMap();
	glDepthFunc(GL_LEQUAL);
	glBindVertexArray(skybox->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
	skybox->cubemap.UnBindCubeMap();



	shaderProgram->UnUse();
};
void SystemRendererSkyMap::OnResizeData(uint32_t ComponentTypeID,std::vector<uint8_t>* data)
{

};