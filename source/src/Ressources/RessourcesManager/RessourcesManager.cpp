#include <Ressources/RessourcesManager/RessourcesManager.h>
#include "ECS/Scene/Scene.h"
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

// Look recursively in all file from projectFolder
// and push path in the queue
void ResourcesManager::ProduceurFunc(const std::string& projectFolder)
{
	fs::path assetsPath(assetsFolder);

	for (const auto& entry : std::filesystem::directory_iterator(projectFolder))
		LookFiles(entry.path());

	

	m_consumerProd.WaitForEveryProducersExpect(std::this_thread::get_id());
	m_consumerProd.EndProduction();	
}

// consume a path to create a Ressources
void ResourcesManager::ConsumersFunc(TheardCP<PRODUCER, CONSUMERS, std::filesystem::path>& production)
{
	while(!production.EndProcess())
	{
		std::unique_lock<std::mutex> lock(production.resourcesMutex);
		production.consumersCv.wait(lock, [&] { return !production.resources.empty(); });
		std::filesystem::path ressourcesPath = production.ConsumersGetValue();
		lock.unlock();


		std::string tostring = ressourcesPath.generic_string();

		if (ResourcesManager::IsModel(tostring))
		{
			CreateOnLoad<Mesh>(ressourcesPath);
			continue;
		}
		else if (ResourcesManager::IsTexture(tostring))
		{
			CreateOnLoad<Texture>(ressourcesPath);
			continue;
		}
		else if (ResourcesManager::IsShader(tostring))
		{
			CreateOnLoad<Shader>(ressourcesPath);
			continue;
		}

	}
}

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
	CubeMaps* SkySkybox = new CubeMaps(cubemapsSkyString);
	PushBackElement<CubeMaps>("SkySkybox", SkySkybox);

	std::chrono::system_clock::time_point timeStart = std::chrono::system_clock::now();

	if (!App::IsMonoThread)
	{
		m_consumerProd.GetProducer(0) = std::thread(&ResourcesManager::ProduceurFunc,this,std::ref(projectFolder));

		for (std::thread& t : m_consumerProd.consumers)
		{
			t = std::thread(&ResourcesManager::ConsumersFunc,this, std::ref(m_consumerProd));
		}
		m_consumerProd.JoinIfJoinableProducers();
		m_consumerProd.JoinIfJoinableConsumers();
	}
	else
	{
		for (const auto& entry : std::filesystem::directory_iterator(projectFolder))
			LookFiles(entry.path());
	}

	// Init all ressources
	if(!App::IsMonoThread)
	for (auto it = m_mainResourcesMap.begin(); it != m_mainResourcesMap.end(); it++)
	{

		it->second->Init();
	}

	PrintTime(timeStart, m_mainResourcesMap.size());
}

void ResourcesManager::DeleteAllasset()
{
	for (auto it = m_mainResourcesMap.begin(); it != m_mainResourcesMap.end(); it++)
	{
		delete it->second;
	}
	m_mainResourcesMap.clear();
	m_consumerProd.Reset();
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
		if(!App::IsMonoThread)
		{
			m_consumerProd.ProducersPushRessoures(path_string);
		}
		else
		{
			Create<Texture>(path);
		}
	}
}

void ResourcesManager::LoadModel(std::filesystem::path path)
{
	
	std::string path_string = path.generic_string();


	if (ResourcesManager::IsModel(path_string))
	{
		if (!App::IsMonoThread)
		{
			m_consumerProd.ProducersPushRessoures(path_string);
		}
		else
		{
			Create<Mesh>(path);
		}
     }
}

void ResourcesManager::LoadShader(std::filesystem::path path)
{
	std::string vertexShader;
	std::string fragmentShader;
	std::string geometry;

	for (const auto& entry : fs::directory_iterator(path))
	{

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

	if(!App::IsMonoThread)
	{
		m_consumerProd.ProducersPushRessoures(path);
	}
	else
	{
		Create<Shader>(path);
	}	

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
		if (entry.is_directory())
		{
			if(App::IsMonoThread)
			{
				LookFiles(entry.path());
				LoadShader(entry.path());
			}
			else
			{
				std::thread* t = m_consumerProd.GetAsleepProducer();

				if (t != nullptr)
				{
					auto l = [&]()
						{
							LookFiles(entry.path());
							LoadShader(entry.path());
						};
					*t = std::thread(l);
				}
				else
				{

					LookFiles(entry.path());
					LoadShader(entry.path());
				}
			}


			

		}

		LoadTexture(entry.path().c_str());
		LoadModel(entry.path().c_str());
		
	}		
		
}