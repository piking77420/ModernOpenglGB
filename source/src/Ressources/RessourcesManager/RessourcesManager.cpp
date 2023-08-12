#include <Ressources/RessourcesManager/RessourcesManager.h>
#include "Ressources/Scene/Scene.h"
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
 
void RessourcesManager::LoadAllAssets(const std::string& projectFolder)
{



	std::vector<std::string> cubemapsSpaceString =
	{
		"ProjectFolder/Project1/assets/cube_maps/skybox/SpaceSkyBox/bkg1_right.png",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SpaceSkyBox/bkg1_left.png",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SpaceSkyBox/bkg1_top.png",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SpaceSkyBox/bkg1_bottom.png",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SpaceSkyBox/bkg1_front.png",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SpaceSkyBox/bkg1_back.png",

	};
	CubeMaps cubemaps(cubemapsSpaceString);
	SkyBox* spaceSkybox = new SkyBox(cubemaps);
	PushBackElement<SkyBox>("SpaceSkyBox", spaceSkybox);

	std::vector<std::string> cubemapsSkyString =
	{
		"ProjectFolder/Project1/assets/cube_maps/skybox/SkySkybox/right.jpg",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SkySkybox/left.jpg",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SkySkybox/top.jpg",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SkySkybox/bottom.jpg",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SkySkybox/front.jpg",
		"ProjectFolder/Project1/assets/cube_maps/skybox/SkySkybox/back.jpg",

	};
	CubeMaps cubemaps2(cubemapsSkyString);
	SkyBox* SkySkybox = new SkyBox(cubemaps2);
	PushBackElement<SkyBox>("SkySkybox", SkySkybox);


	fs::path assetsPath(assetsFolder);

	for (const auto& entry : fs::directory_iterator(projectFolder))
		LookFiles(entry.path());


	std::string pathToCube = "Ressources/BasePrimitive/cube.obj";
	std::thread* newThreads1 = new std::thread([this, pathToCube]()
		{
			Create<Mesh>(pathToCube);
		});
	theards.push_back(newThreads1);

	std::string pathToSphere = "Ressources/BasePrimitive/Sphere.obj";
	std::thread* newThreads2 = new std::thread([this, pathToSphere]()
		{
			Create<Mesh>(pathToSphere);
		});
	theards.push_back(newThreads2);
	std::string pathToplane = "Ressources/BasePrimitive/plane.obj";
	std::thread* newThreads3 = new std::thread([this, pathToplane]()
		{
			Create<Mesh>(pathToplane);
		});
	theards.push_back(newThreads3);




	// Join threads + clear vector
	if(!theards.empty())
	for (size_t i = 0; i < theards.size(); i++)
	{
		theards[i]->join();
		delete theards[i];
	}
	theards.clear();



	// Init all ressources
	for (auto it = m_MainResourcesMap.begin(); it != m_MainResourcesMap.end(); it++)
	{
		it->second->Init();
	}




}


std::map<std::string, IResource*>& RessourcesManager::GetRessources()
{
	return m_MainResourcesMap;
}

RessourcesManager::~RessourcesManager()
{

	for (auto it = m_MainResourcesMap.begin(); it != m_MainResourcesMap.end(); it++)
	{
		delete it->second;
	}
	m_MainResourcesMap.clear();	
}


bool RessourcesManager::isThisValidForThisFormat(std::string path, std::string format)
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



fs::path RessourcesManager::CreatMetaDataFile(const fs::path& FilePath,const std::string& FileName)
{
	
	std::lock_guard<std::mutex> lock(fileMutex);
		
	
	
	std::ofstream File(FilePath.generic_string() + ".metaData");
	if (File.is_open())
	{
		//File << name << std::endl;
		File.close();
		LOG("File created: " + FilePath.generic_string() + ".metaData",STATELOG::GOOD);
	}
	else
	{
		LOG("Failed to open file: " + FilePath.generic_string() + ".metaData", STATELOG::WARNING);
	}

	return fs::path(FilePath.generic_string() + ".metaData");
}


void RessourcesManager::LoadTexture(fs::path path)
{
	std::string path_string = path.generic_string();


	if (isThisValidForThisFormat(path_string, png) || isThisValidForThisFormat(path_string, jpg))
	{
		std::thread* newThreads = new std::thread([this, path_string]()
			{
				Create<Texture>(path_string);
			});
		theards.push_back(newThreads);

	}
}




void RessourcesManager::LoadModel(std::filesystem::path path)
{
	/*
	std::string path_string = path.generic_string();


	if (isThisValidForThisFormat(path_string, obj))
	{
		std::thread* newThreads = new std::thread([this, path_string]()
			{
				Create<Mesh>(path_string);
			});
		theards.push_back(newThreads);
	}*/
}

void RessourcesManager::LoadShader(std::filesystem::path path)
{
	std::string vertexShader;
	std::string fragmentShader;
	std::string geometry;

	for (const auto& entry : fs::directory_iterator(path))
	{

		if (isThisValidForThisFormat(entry.path().string(), vertexShaderFormat))
		{
			vertexShader = entry.path().string();
			Create<ShaderSource>(vertexShader);
		}

		if (isThisValidForThisFormat(entry.path().string(), fragmentShaderFormat))
		{
			fragmentShader = entry.path().string();
			Create<ShaderSource>(fragmentShader);
		}

		if (isThisValidForThisFormat(entry.path().string(), geometryShaderFormat))
		{
			geometry = entry.path().string();
		}


	}

	if (fragmentShader.size() == 0 || vertexShader.size() == 0)
		return;

	std::string ressourcesName = path.filename().string();

	
	std::thread* newThreads = new std::thread([this, vertexShader , fragmentShader , geometry , ressourcesName]()
		{
			Shader* newShader = nullptr;

			if (geometry.empty())
			{
				newShader = new Shader(vertexShader.c_str(), fragmentShader.c_str(), ressourcesName);
			}
			else
			{
				newShader = new Shader(vertexShader.c_str(), fragmentShader.c_str(), geometry.c_str(), ressourcesName);

			}
			PushBackElement<Shader>(ressourcesName, newShader);

		});

	theards.push_back(newThreads);
	
}









RessourcesManager::RessourcesManager()
{
}

void RessourcesManager::LookFiles(fs::path _path)
{
	if (_path.empty() || _path.filename().string() == cubeMapsFolder)
	{
		return;
	}

	for (const auto& entry : fs::directory_iterator(_path))
	{
		LoadTexture(entry.path().c_str());
		LoadModel(entry.path().c_str());

		if (entry.is_directory())
		{
			LookFiles(entry.path());
			LoadShader(entry.path().c_str());

		}
	}

	
			
		
}