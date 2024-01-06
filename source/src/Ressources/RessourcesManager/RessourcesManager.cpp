#include <Ressources/RessourcesManager/RessourcesManager.h>
#include "Core/ECS/Scene.h"
#include "LowRenderer/Cam/Camera.h"
#include<Ressources/Texture/Texture.hpp>
#include "Ressources/Shader/Shader.h"
#include "Ressources/Mesh/Mesh.h"
#include "Ressources/Shader/ShaderSource/ShaderSource.hpp"
#include "LowRenderer/FrameBuffer/DepthMap/Depthmap.h"
#include "LowRenderer/FrameBuffer/ShadowMap/ShadowMaps.h"
#include "LowRenderer/FrameBuffer/MultiSamples/MultiSamples.h"
#include "Ressources/SkyBox/SkyBox.h"
#include "Ressources/CubeMaps/CubeMaps.h"
#include<ostream>
#include "App/App.h"

void PrintTime(std::chrono::system_clock::time_point& start,int mapzize)
{
	LOG(" There is " + std::to_string(mapzize) + " ", STATELOG::WARNING);
	std::chrono::system_clock::time_point timeEnd = std::chrono::system_clock::now();
	if (App::IsMonoThread)
	{
		std::cout << "With monothreading it takes : " << std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - start).count() << " milliseconds\n" << std::endl;
	}
	else
	{
		std::cout << "With multhithreading it takes : " << std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - start).count() << " milliseconds\n" << std::endl;
	}
	LOG("App::IsMonoThread = " + std::to_string(App::IsMonoThread) + " ", STATELOG::WARNING);
}

void ResourcesManager::LoadAllAssets(const std::string& projectFolder)
{
	std::vector<std::string> cubemapsSkyString =
	{
		"ProjectFolder/Project1/assets/cube_maps/skybox/SkySkybox/right.jpg",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SkySkybox/left.jpg",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SkySkybox/top.jpg",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SkySkybox/bottom.jpg",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SkySkybox/front.jpg",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SkySkybox/back.jpg",

	};

	CubeMaps* SkySkybox = new CubeMaps(cubemapsSkyString, TextureFlags::NONEFLAG);
	PushBackElement<CubeMaps>("SkySkybox", SkySkybox);



	CubeMaps* textureHdr = new CubeMaps("ProjectFolder/Project1/assets/cube_maps/skybox.hdr");
	PushBackElement<CubeMaps>("skybox", textureHdr);


	std::chrono::system_clock::time_point timeStart = std::chrono::system_clock::now();

	
	
	for (const auto& entry : std::filesystem::directory_iterator(projectFolder))
			LookFiles(entry.path());
	

	for (auto it = m_mainResourcesMap.begin(); it != m_mainResourcesMap.end(); it++)
	{
		it->second->InitResource();
	}

	PrintTime(timeStart, (int)m_mainResourcesMap.size());
}

void ResourcesManager::DeleteAllasset()
{
	for (auto it = m_mainResourcesMap.begin(); it != m_mainResourcesMap.end(); it++)
	{
		delete it->second;
	}
	m_mainResourcesMap.clear();
}

void ResourcesManager::SetCameraInfoForShader(Camera* cam)
{

	for (auto it = m_mainResourcesMap.begin(); it != m_mainResourcesMap.end(); it++)
	{
		Shader* currentShader = dynamic_cast<Shader*>(it->second);
		if (currentShader != nullptr)
		{
			currentShader->Use();
			currentShader->SetMatrix("VP", cam->GetVp().GetPtr());
			currentShader->SetMatrix("view", cam->GetLookMatrix().GetPtr());
			currentShader->SetVector3("viewPos", &cam->eye.x);

			currentShader->UnUse();

		}
	}
}

bool ResourcesManager::IsThisValidForThisFormat(std::string path, std::string format)
{
	size_t startFileFormat = path.size() - format.size();
	int counter = 0;
	for (size_t i = startFileFormat; i < path.size(); i++)
	{
		if (path[i] == format[i - startFileFormat])
			counter++;
	}
	if (counter == format.size())
		return true;

	return false;
}




bool ResourcesManager::IsTexture(std::string path_string)
{
	if (IsThisValidForThisFormat(path_string, png) || IsThisValidForThisFormat(path_string, jpg))
	{
		return true;
	}

	return false;
}

bool ResourcesManager::IsModel(std::string path_string)
{
	if (IsThisValidForThisFormat(path_string, obj))
	{
		return true;
	}
	return false;

}

bool ResourcesManager::IsShader(std::string path_string)
{
	std::string vertexShader;
	std::string fragmentShader;

	for (const auto& entry : fs::directory_iterator(path_string))
	{

		if (IsThisValidForThisFormat(entry.path().string(), vertexShaderFormat))
		{
			vertexShader = entry.path().string();
		}

		if (IsThisValidForThisFormat(entry.path().string(), fragmentShaderFormat))
		{
			fragmentShader = entry.path().string();
		}
	}

	if (fragmentShader.size() == 0 || vertexShader.size() == 0)
		return false;

	return true;
}



void ResourcesManager::LoadTexture(fs::path path)
{
	std::string path_string = path.generic_string();

	if (ResourcesManager::IsTexture(path_string))
	{
		Create<Texture>(path);		
	}
}

void ResourcesManager::LoadModel(std::filesystem::path path)
{
	
	std::string path_string = path.generic_string();


	if (ResourcesManager::IsModel(path_string))
	{
		Create<Mesh>(path);
		
    }
}

bool IsPythonCacheFile(const fs::path& filePath) {
	return filePath.extension() == ".pyc";
}


void ResourcesManager::LoadShader(std::filesystem::path path)
{
	std::string vertexShader;
	std::string fragmentShader;
	std::string geometry;
	
	for (const fs::directory_entry& entry : fs::directory_iterator(path))
	{
		const auto permissions = fs::status(entry.path()).permissions();

		// Skip Python cache files
		if (IsPythonCacheFile(entry.path()))
			continue;


		if (IsThisValidForThisFormat(entry.path().string(), vertexShaderFormat))
		{
			vertexShader = entry.path().string();
		}

		if (IsThisValidForThisFormat(entry.path().string(), fragmentShaderFormat))
		{
			fragmentShader = entry.path().string();
		}
		if (IsThisValidForThisFormat(entry.path().string(), geometryShaderFormat))
		{
			geometry = entry.path().string();
		}
	}
	
	if (fragmentShader.size() == 0 || vertexShader.size() == 0)
		return;


	Create<Shader>(path);	

}

// Look In the folder
void ResourcesManager::LookFiles(fs::path _path)
{
	if (_path.empty())
	{
		return;
	}
	
	for (const auto& entry : fs::directory_iterator(_path))
	{
		if (entry.path().stem().generic_string() == "__pycache__")
			continue;

		if (entry.is_directory())
		{
			LookFiles(entry.path());
			LoadShader(entry.path());

		}
		LoadTexture(entry.path().c_str());
		LoadModel(entry.path().c_str());
		
	}		
		
}

