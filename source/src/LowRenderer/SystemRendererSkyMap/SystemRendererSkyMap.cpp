#include "LowRenderer/SystemRendererSkyMap/SystemRendererSkyMap.hpp"
#include "ECS/Scene.h"
#include "Physics/Transform/Transform.hpp"
#include "Core/DataStructure/Project.hpp"


void SystemRendererSkyMap::Init(Scene* scene)
{
	cubemap = ResourcesManager::GetElement<CubeMapHdr>("NightCity");

	shaderProgram = ResourcesManager::GetElement<Shader>("EquirectangularToCubemapShader");

	cubemap->InitCubeMap(shaderProgram);
	shaderProgram = ResourcesManager::GetElement<Shader>("BackgroundShader");
}

void SystemRendererSkyMap::Render(Scene* scene)
{
	DrawCubeMap();
}

void SystemRendererSkyMap::Update(Scene* scene)
{

	ImGui::Begin("ChangeCubeMap", &m_OpenChangeCubeMap);

		
		std::vector<std::pair<std::string, CubeMapHdr*>> cubeMap = ResourcesManager::GetAllElementOfType<CubeMapHdr>();

		for (size_t i = 0; i < cubeMap.size(); i++)
		{
			if(ImGui::Button(cubeMap[i].first.c_str()))
			{
				if (cubemap == cubeMap[i].second)
					break;

				cubemap = cubeMap[i].second;
				shaderProgram = ResourcesManager::GetElement<Shader>("EquirectangularToCubemapShader");
				cubemap->InitCubeMap(shaderProgram);
				shaderProgram = ResourcesManager::GetElement<Shader>("BackgroundShader");

			}

		}

			ImGui::DragFloat("IridianceFactor", &irridianceFactor, 1, 0, 10);
		
	ImGui::End();
	


}

void SystemRendererSkyMap::DrawCubeMap()
{

	shaderProgram->Use();

	shaderProgram->SetInt("environmentMap", 0);
	shaderProgram->SetMatrix("projection", Camera::GetMainCamera()->GetProjectionMatrix().GetPtr());
	shaderProgram->SetMatrix("view", Camera::GetMainCamera()->GetLookMatrix().GetPtr());

	glActiveTexture(GL_TEXTURE0);
	cubemap->BindEnvCubeMap();

	cubemap->DrawCube();
	shaderProgram->UnUse();
}

