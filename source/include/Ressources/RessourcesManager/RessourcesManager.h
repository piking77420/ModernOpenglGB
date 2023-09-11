#pragma once
#include <Ressources/IResources/IResource.h>
#include <Core/Debug/LogClass.h>
#include <Core/Debug/AssertClass.h>
#include "Ressources/Mesh/Mesh.h"
#include <thread>

#include<filesystem>
#include<unordered_map>
#include<map>
#include<mutex>

#include<string>

#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>


class Camera;






class RessourcesManager
{
public:

	// Return map for iterator  to camera set uniform
	std::map<std::string, IResource*>& GetRessources();
	void LoadAllAssets(const std::string& projectFolder);
	template<class T>
	void Remove(const std::string& name);
	template<class T>
	void PushBackElement(std::string name, T* newElement);
	template<class T>
	T* GetElement(const std::string& name);

	template<class T>
	const T* GetElement(const std::string& name) const ;

	template<class T>
	void Create(const fs::path& FilePath);
	template<class T>
	bool IsRessourcesIs(IResource* ressources) const ;
	template<class T>
	T* TryIsTypeOf(IResource* ressources) const;
	


	RessourcesManager();
	~RessourcesManager();
private:
	std::mutex ressourcesMutex;
	std::map<std::string, IResource*> m_MainResourcesMap;
	void LoadTexture(std::filesystem::path path);
	void LookFiles(std::filesystem::path _path);
	void LoadModel(std::filesystem::path path);
	void LoadShader(std::filesystem::path path);
	bool isThisValidForThisFormat(std::string path, std::string format);
	fs::path CreatMetaDataFile(const fs::path& FilePath, const std::string& FileName);


	// Texture file accetptes jpg png 
	const std::string png = ".png";
	const std::string jpg = ".jpg";
	// Model file supported obj
	const std::string obj = ".obj";
	// Shader Files format
	const std::string vertexShaderFormat = ".vert";
	const std::string fragmentShaderFormat = ".frag";
	const std::string geometryShaderFormat = ".geom";
	// Scene Format
	const std::string sceneFormat = ".scene";
	// Assets Folder
	const std::string assetsFolder = "assets";
	// cubeMaps folder to ignore not supported TO DO	
	const std::string cubeMapsFolder = "cube_maps";
	std::vector<std::thread*> theards;

};



template<class T>
inline void RessourcesManager::PushBackElement(std::string name, T* newElement)
{
	IResource* test = dynamic_cast<IResource*>(newElement);
	
	Debug::Assert->Assertion(test);


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
	LOG(outputMessage,STATELOG::WARNING);

	return nullptr;
}



template<class T>
inline const T* RessourcesManager::GetElement(const std::string& name) const
{
	auto wanted = (m_MainResourcesMap.find(name));

	if (wanted != m_MainResourcesMap.end())
	{
		return dynamic_cast<const T*>(wanted->second);
	}
	std::string nameofTemplate = typeid(T).name();
	std::string outputMessage = " There is no " + nameofTemplate + " name as " + name;
	LOG(outputMessage, STATELOG::WARNING);

	return nullptr;
}

template<class T>
inline void RessourcesManager::Create(const fs::path& FilePath)
{	
		T* newRessources = new T(FilePath);
		IResource* test = dynamic_cast<IResource*>(newRessources);

		if (!test)
			return;
		std::string Correctname = FilePath.filename().generic_string();
			// test->PathtoMetaDataFile = CreatMetaDataFile(FilePath, Correctname);



			if (m_MainResourcesMap.contains(Correctname))
			{
				ressourcesMutex.lock();
				auto currentRessources = m_MainResourcesMap.find(Correctname);
				delete currentRessources->second;
				currentRessources->second = newRessources;
				ressourcesMutex.unlock();
				return ;

			}

			ressourcesMutex.lock();

			m_MainResourcesMap.insert({ Correctname,newRessources });
			auto returned = m_MainResourcesMap.find(Correctname);

			ressourcesMutex.unlock();


}

template<class T>
inline bool RessourcesManager::IsRessourcesIs(IResource* ressources) const
{
	T* ptrTest = dynamic_cast<T*>(ressources);

	if (!ptrTest)
		return false;

	return true;
}

template<class T>
inline T* RessourcesManager::TryIsTypeOf(IResource* ressources) const
{

	T* ptrTest = dynamic_cast<T*>(ressources);

	if(ptrTest)
	{
		return ptrTest;
	}


	return nullptr;
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


