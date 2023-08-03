#include "LowRenderer/SystemRendererSkyMap/SystemRendererSkyMap.hpp"
#include "Ressources/Scene/Scene.h"
#include "Physics/Transform/Transform.hpp"
#include "Core/DataStructure/Project.hpp"
#include "Ressources/SkyBox/SkyBox.h"


void SystemRendererSkyMap::Init(Scene* scene)
{
	shaderProgram = scene->currentproject->ressourcesManager.GetElement<Shader>("SkyBoxShader");
	skybox = scene->currentproject->ressourcesManager.GetElement<SkyBox>("SkySkybox");

	shaderProgram->Use();
	shaderProgram->SetInt("skybox", 30);
	
}

void SystemRendererSkyMap::Awake(Scene* scene)
{
}

void SystemRendererSkyMap::Render(Scene* scene)
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
}
