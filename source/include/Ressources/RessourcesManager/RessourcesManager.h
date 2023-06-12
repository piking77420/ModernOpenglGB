#pragma once
#include <Ressources/IResources/IResource.h>
#include <Core/Debug/LogClass.h>
#include <Core/Debug/AssertClass.h>
#include "Ressources/Model/Model.h"


#include<filesystem>
#include<unordered_map>
#include<string>

#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>

// Make a rules for template is not bas of Iressources = error
template<class T>
concept IResourceClass = std::is_base_of<IResource, T>::value;

class Camera;

class RessourcesManager
{
public:
	static std::string GetRessourcesName(const std::string& path);
	
	// Return map for iterator  to camera set uniform
	std::unordered_map<std::string, IResource*>& GetRessources();
	void LoadAllAssets();
	template<class T>
	void Remove(const std::string& name);
	template<class IResource>
	void PushBackElement(std::string name, IResource* newElement);
	template<class T>
	T* GetElement(const std::string& name);
	template<class T>
	T* Create(std::string name);
	

	void RealoadAllTexture();
	RessourcesManager();
	~RessourcesManager();
private:

	std::unordered_map<std::string, IResource*> m_MainResourcesMap;
	void LoadTexture(std::filesystem::path path);
	void LookFiles(std::filesystem::path _path);
	void LoadModel(std::filesystem::path path);
	void LoadShader(std::filesystem::path path);


	// Texture file accetptes jpg png 
	const std::string png = ".png";
	const std::string jpg = ".jpg";
	// Model file supported obj
	const std::string obj = ".obj";
	// Shader Files format
	const std::string vertexShaderFormat = ".vertex";
	const std::string fragmentShaderFormat = ".frag";
	const std::string geometryShaderFormat = ".geom";

	// Assets Folder
	const std::string assetsFolder = "assets";
	// cubeMaps folder to ignore not supported TO DO	
	const std::string cubeMapsFolder = "cube_maps";
};

static RessourcesManager* StaticRessourcesManger;


template<class IResource>
inline void RessourcesManager::PushBackElement(std::string name, IResource* newElement)
{
	if (m_MainResourcesMap.contains(name))
	{
		auto currentRessources = m_MainResourcesMap.find(name);
		delete currentRessources->second;
		currentRessources->second = newElement;
		return;

	}

	m_MainResourcesMap.insert({ name, newElement });
}

template<class T>
inline T* RessourcesManager::GetElement(const std::string& name)
	{
	auto wanted = (m_MainResourcesMap.find(name));

	if (wanted != m_MainResourcesMap.end())
	{
		return dynamic_cast<T*>(wanted->second);
	}
	std::string nameofTemplate = typeid(T).name();
	std::string outputMessage = " There is no " + nameofTemplate + " name as " + name;
	Debug::Log->LogWarning(outputMessage);

	return nullptr;
}

// if it's a path he will automaticaly return the correct name
template<class T>
inline T* RessourcesManager::Create(std::string name)
{
	T* newRessources = new T(name);
	std::string Correctname = GetRessourcesName(name);

	if (m_MainResourcesMap.contains(Correctname))
	{
		auto currentRessources = m_MainResourcesMap.find(name);
		delete currentRessources->second;
		currentRessources->second = newRessources;
		return newRessources;

	}


	m_MainResourcesMap.insert({ Correctname,newRessources });
	auto returned = m_MainResourcesMap.find(Correctname);

	return newRessources;
}



template<class T>
inline void RessourcesManager::Remove(const std::string& name)
{

	auto wanted = (m_MainResourcesMap.find(name));

	if (wanted != m_MainResourcesMap.end())
	{
		delete wanted->second;
		m_MainResourcesMap.erase(wanted);
	}

}


