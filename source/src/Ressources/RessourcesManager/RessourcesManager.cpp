#include <Ressources/RessourcesManager/RessourcesManager.h>
#include "LowRenderer/Cam/Camera.h"
#include<Ressources/Texture/Texture.hpp>
#include "Ressources/Shader/Shader.h"
#include "LowRenderer/Light/Light.h"
#include "Ressources/Model/Model.h"


namespace fs = std::filesystem;


void RessourcesManager::LoadAllAssets()
{
	fs::path assetsPath(this->assetsFolder);

	for (const auto& entry : fs::directory_iterator(assetsPath))
		LookFiles(entry.path());

	

}


std::unordered_map<std::string, IResource*>& RessourcesManager::GetRessources()
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


bool isThisValidForThisFormat(std::string path, std::string format)
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





void RessourcesManager::LoadTexture(fs::path path)
{
	std::string path_string = path.generic_string();

	if (isThisValidForThisFormat(path_string, png) || isThisValidForThisFormat(path_string, jpg))
	{
		Texture* tex = new Texture(path_string);
		Debug::Log->LogGood(path_string + " has been Correcty loaded");

		Create<Texture>(path_string);
	}
}

std::string RessourcesManager::GetRessourcesName(const std::string& path)
{
	std::string name;

	if(path.contains('/'))
	{
		for (size_t i = path.find_last_of('/') + 1; i < path.size(); i++)
		{
			name.push_back(path[i]);
		}
		return name;

	}
	return path;
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
		}

		if (isThisValidForThisFormat(entry.path().string(), fragmentShaderFormat))
		{
			fragmentShader = entry.path().string();

		}

		if (isThisValidForThisFormat(entry.path().string(), geometryShaderFormat))
		{
			geometry = entry.path().string();

		}

	}

	if (fragmentShader.size() == 0 || vertexShader.size() == 0)
		return;

	std::string ressourcesName = path.filename().string();

	Shader* newShader = new Shader(vertexShader.c_str(), fragmentShader.c_str(), geometry.c_str(), ressourcesName);
	PushBackElement<Shader>(ressourcesName, newShader);


}






void RessourcesManager::RealoadAllTexture()
{
	
	for (auto it = m_MainResourcesMap.begin(); it != m_MainResourcesMap.end(); it++)
	{
		Texture* texture = dynamic_cast<Texture*>(it->second);

		if (texture != nullptr)
			texture->UpdateTextureToGammaCorrection();
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
		
		LoadTexture(entry.path().c_str());
		LoadModel(entry.path().c_str());

		if(entry.is_directory())
		{
			LookFiles(entry.path());
			LoadShader(entry.path().c_str());

		}
	}
}