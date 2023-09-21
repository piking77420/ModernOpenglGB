#pragma once
#include <Ressources/IResources/IResource.h>
#include <Core/Debug/LogClass.h>
#include <Core/Debug/AssertClass.h>
#include "Ressources/Mesh/Mesh.h"
#include <Core/CoreEngine.h>
#include<filesystem>
#include<unordered_map>
#include<map>


#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include "Core/ThreadPatern/TheardCP.h"

class Camera;


#define PRODUCER 1
#define CONSUMERS 5

class ResourcesManager
{
public:

	ResourcesManager()
	{
	}
	~ResourcesManager()
	{
		// delete all ressources
		for (auto it = m_mainResourcesMap.begin(); it != m_mainResourcesMap.end(); it++)
		{
			delete it->second;
		}
		m_mainResourcesMap.clear();
	}

	void SetCameraInfoForShader(Camera* cam);
	
	// function to load all asset in projectFolder
	void LoadAllAssets(const std::string& projectFolder);

	void DeleteAllasset();
	
	template<class T>
	void Remove(const std::string& name);
	
	template<class T>
	void PushBackElement(std::string name, T* newElement);
	
	template<class T>
	T* GetElement(const std::string& name);

	template<class T>
	const T* GetElement(const std::string& name) const ;

	template<class T>
	void GetResource(std::future<T*>& futureResource,std::string name)
	{
		std::promise<T*> promise;
		futureResource = promise.get_future();

		// Create a thread to handle promise
		auto l = [&](std::string _name) {
			try
			{
				T* ressource = GetElement<T>(_name);
				promise.set_value(ressource);

				
			}
			catch (const std::exception& e)
			{
				promise.set_exception(std::current_exception());
			}
			};

		std::async(std::launch::async,
			l, name);

		
	}


	template<class T>
	void GetResource(std::future<const T*>& futureResource,std::string name)
	{
		std::promise<const T*> promise;
		futureResource = promise.get_future();

		// Create a thread to handle promise
		auto l = [&](std::string _name) {
			try
			{
				const T* ressource = GetElement<T>(_name);
				promise.set_value(ressource);


			}
			catch (const std::exception& e)
			{
				promise.set_exception(std::current_exception());
			}
			};

		std::async(std::launch::async,
			l, name);
	}


	template<class T>
	void Create(const fs::path& FilePath);
	
	std::mutex resourcesMutex;	

	static bool IsTexture(std::string path_string);
	static bool IsModel(std::string path_string);
	static bool IsShader(std::string path_string);

	static bool IsThisValidForThisFormat(std::string path, std::string format);


	static constexpr std::string GetVertexShaderFormat() { return ResourcesManager::vertexShaderFormat; }
	static constexpr std::string GetFragmentShaderFormat() { return ResourcesManager::fragmentShaderFormat; }
	static constexpr std::string GetGeometryShaderFormat() { return ResourcesManager::geometryShaderFormat; }


private:


	TheardCP<PRODUCER ,CONSUMERS, std::filesystem::path> m_consumerProd;
	std::map<std::string, IResource*> m_mainResourcesMap;

	// Look for 
	void LoadTexture(std::filesystem::path path);
	void LoadModel(std::filesystem::path path);	
	void LoadShader(std::filesystem::path path);

	// Look in the project folder rescursively to push resources path
	void LookFiles(std::filesystem::path _path);

	// On Load Func //

	void ProduceurFunc(const std::string& projectFolder);
	void ConsumersFunc(TheardCP<PRODUCER, CONSUMERS, std::filesystem::path>& production);
	template<class T>
	void CreateOnLoad(std::filesystem::path path);

	/////////////////

	// Texture file accetptes jpg png 
	static inline const std::string png = ".png";
	static inline const std::string jpg = ".jpg";
	// Model file supported obj
	static inline const std::string obj = ".obj";
	// Shader Files format
	static inline const std::string vertexShaderFormat = ".vert";
	static inline const std::string fragmentShaderFormat = ".frag";
	static inline const std::string geometryShaderFormat = ".geom";
	// Scene Format
	static inline const std::string sceneFormat = ".scene";
	// Assets Folder
	static inline const std::string assetsFolder = "assets";
};




template<class T>
inline T* ResourcesManager::GetElement(const std::string& name)
	{
	
	auto wanted = (m_mainResourcesMap.find(name));

	if (wanted != m_mainResourcesMap.end())
	{
		return dynamic_cast<T*>(wanted->second);
	}
	std::string nameofTemplate = typeid(T).name();
	std::string outputMessage = " There is no " + nameofTemplate + " name as " + name;
	LOG(outputMessage,STATELOG::WARNING);

	return nullptr;
}



template<class T>
inline const T* ResourcesManager::GetElement(const std::string& name) const
{
	auto wanted = (m_mainResourcesMap.find(name));

	if (wanted != m_mainResourcesMap.end())
	{
		return dynamic_cast<const T*>(wanted->second);
	}
	std::string nameofTemplate = typeid(T).name();
	std::string outputMessage = " There is no " + nameofTemplate + " name as " + name;
	LOG(outputMessage, STATELOG::WARNING);

	return nullptr;
}

template<class T>
inline void ResourcesManager::Create(const fs::path& FilePath)
{
	std::string toString = FilePath.generic_string();
	T* newResources = new T(FilePath);


	if (m_mainResourcesMap.contains(toString))
	{
		auto currentResources = m_mainResourcesMap.find(toString);
		delete currentResources->second;
		currentResources->second = newResources;
		return;
	}
	m_mainResourcesMap.insert({ FilePath.filename().generic_string(),newResources});
	newResources->Init();
	
}

template<class T>
inline void ResourcesManager::PushBackElement(std::string name, T* newElement)
{
	if (m_mainResourcesMap.contains(name))
	{
		auto currentResources = m_mainResourcesMap.find(name);
		delete currentResources->second;
		currentResources->second = newElement;
		return;
	}

	m_mainResourcesMap.insert({ name, newElement });
	newElement->Init();
}

template<class T>
inline void ResourcesManager::CreateOnLoad(std::filesystem::path path)
{
	std::string toString = path.filename().generic_string();
	T* newResources = new T(path);

	std::lock_guard<std::mutex> lock(resourcesMutex);

	if (m_mainResourcesMap.contains(toString))
	{
		auto currentResources = m_mainResourcesMap.find(toString);
		delete currentResources->second;
		currentResources->second = newResources;
		return;
	}

	m_mainResourcesMap.insert({ toString, newResources });
	
}


template<class T>
inline void ResourcesManager::Remove(const std::string& name)
{

	auto wanted = (m_mainResourcesMap.find(name));

	if (wanted != m_mainResourcesMap.end())
	{
		delete wanted->second;
		m_mainResourcesMap.erase(wanted);
	}

}


