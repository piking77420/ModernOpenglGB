#pragma once
#include<vector>
#include <unordered_map>
#include "Ressources/RessourcesManager/RessourcesManager.h"


// ECS // 
#include "Core/ECS/Entity.h"
#include "Core/ECS/Register.h"

#ifndef SWIG
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#endif 

#include "LowRenderer/Renderer/Renderer.hpp"



class FrameBuffer;
class Project;
class Shader;

class Scene 
{
public :


	void Init();

	void Awake();
	void Start();

	void DrawGizmo();

	void FixedUpdate();
	void Update();
	void LateUpdate();

	void Render(Shader& shader);
	void RenderScene(Shader& shader);


	Entity* CreateEntity();

	Entity* GetEntities(uint32_t ID);


	template<class T>
	bool IsEntityHas(const Entity* entity);

	template<class T>
	T* TryGetComponent(const Entity* entity);

	template<class T>
	inline void AddComponent(Entity* entity)
	{
		m_registerScene.AddComponentInternal(T::componentTypeID, entity);
	}

	void AddComponent(uint32_t componentTypeID, Entity* entity)
	{
		m_registerScene.AddComponentInternal(componentTypeID, entity);
	}

	template<class T>
	inline T* GetComponent(Entity* entity)
	{
		return reinterpret_cast<T*>(m_registerScene.GetComponentInternal(T::componentTypeID, entity));
	}

		
	inline bool HasComponent(uint32_t componentTypeID,const  Entity* entity)
	{
		const Component* ptr = m_registerScene.GetComponentInternal(componentTypeID, entity);
		return ptr;	
	}

	template<class T>
	inline const T* GetComponent(Entity* entity) const 
	{
		return reinterpret_cast<const T*>(m_registerScene.GetComponentInternal(T::ComponentTypeID, entity));
	}
	

	template<class T>
	inline void RemoveComponent(Entity* entity)
	{
		m_registerScene.RemoveComponentInternal(T::ComponentTypeID, entity);
	}

	inline void RemoveEntity(Entity* entity)
	{
		m_registerScene.RemoveEntityInternal(entity);
	}


	inline void AddSystem(IEcsSystem* system)
	{
		m_registerScene.AddSystemInternal(system);
	}

	template<class T>
	inline const T* GetSystem() const 
	{
		for (IEcsSystem* system : m_registerScene.systems)
		{
			const T* systemToReturn = dynamic_cast<const T*>(system);
			if(systemToReturn)
				return systemToReturn;
		}
	}


	template<class T>
	inline T* GetSystem() 
	{
		for (IEcsSystem* system : m_registerScene.systems)
		{
			if (dynamic_cast<T*>(system))
				return dynamic_cast<T*>(system);
		}
	}

	template<class T>
	inline void RemoveSystem()
	{

		for (IEcsSystem* system : m_registerScene.systems)
		{
			if (dynamic_cast<T*>(system))
			{
				m_registerScene.systems.erase(system);
			}
		}
	}

	template<class T>
	std::vector<T>* GetComponentDataArray()
	{
		return  reinterpret_cast<std::vector<T>*>(m_registerScene.ComponentsData[T::componentTypeID].second);
	}

	std::vector<uint8_t>* GetComponentDataArray(uint32_t ID)
	{
		return m_registerScene.ComponentsData[ID].second;
	}

	template<class T>
	const std::vector<uint8_t>* GetComponentDataArray() const 
	{
		return m_registerScene.ComponentsData[T::componentTypeID].second;
	}

	const std::vector<uint8_t>* GetComponentDataArray(uint32_t ID) const
	{
		return m_registerScene.ComponentsData[ID].second;
	}

#ifndef SWIG




#endif // !SWIG



	std::string sceneName = "Scene";
	ImGuiIO io;
	float  deltatime;
	Project* currentProject;
	Renderer renderer;

	Scene(std::string name);
	~Scene();

	Register m_registerScene;
private:
};

template<class T>
inline bool Scene::IsEntityHas(const Entity* entity)
{
	uint32_t componentID = T::componentTypeID;

	if (entity->entityComponents[componentID] != ComponentNULL)
		return true;

	return false;
}

template<class T>
inline T* Scene::TryGetComponent(const Entity* entity)
{
	if (!IsEntityHas<T>(entity))
		return nullptr;

	return entity->entityComponents[T::componentID];
}
