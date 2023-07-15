#include <Ressources/RessourcesManager/RessourcesManager.h>
#include "Ressources/Scene/Scene.h"
#include "LowRenderer/Cam/Camera.h"
#include<Ressources/Texture/Texture.hpp>
#include "Ressources/Shader/Shader.h"
#include "LowRenderer/Light/Light.h"
#include "Ressources/Model/Model.h"
#include "Ressources/Shader/ShaderSource/ShaderSource.hpp"

#include<ostream>
 
void RessourcesManager::LoadAllAssets()
{
	fs::path assetsPath(assetsFolder);

	for (const auto& entry : fs::directory_iterator(assetsPath))
		LookFiles(entry.path());

	// Join threads + clear vector

	if(!theards.empty())
	for (size_t i = 0; i < theards.size(); i++)
	{
		theards[i]->join();
		delete theards[i];
	}
	theards.clear();

	/*
	for (auto it = m_MainResourcesMap.begin(); it != m_MainResourcesMap.end(); it++)
	{
		std::cout << it->second->PathtoMetaDataFile << std::endl;
	}*/


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
		Create<Texture>(path_string);
		
	}
}

void RessourcesManager::OnResizeWindow()
{
	for (auto it = m_MainResourcesMap.begin(); it != m_MainResourcesMap.end(); it++)
	{
		it->second->OnWindowResize();
	}
}


void RessourcesManager::LoadModel(std::filesystem::path path)
{
	std::string path_string = path.generic_string();


	if (isThisValidForThisFormat(path_string, obj))
	{
		Create<Model>(path_string);
	}
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
			Shader* newShader = new Shader(vertexShader.c_str(), fragmentShader.c_str(), geometry.c_str(), ressourcesName);
			PushBackElement<Shader>(ressourcesName, newShader);

		});

	theards.push_back(newThreads);
	
}

void RessourcesManager::LoadScene(std::filesystem::path path)
{
	std::string path_string = path.generic_string();

	if (isThisValidForThisFormat(path_string, sceneFormat))
	{
		Create<Scene>(path_string);
	}

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
		LoadScene(entry.path().c_str());
		LoadTexture(entry.path().c_str());
		LoadModel(entry.path().c_str());

		if (entry.is_directory())
		{
			LookFiles(entry.path());
			LoadShader(entry.path().c_str());

		}
	}

	
			
		
}