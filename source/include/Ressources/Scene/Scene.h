#pragma once
#include<vector>
#include "Ressources/IResources/IResource.h"
#include <unordered_map>
#include "Physics/PhysicsEngine.h"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "LowRenderer/Gizmo/Gizmo.h"

// ECS // 
#include "Core/ECS/Entity.h"
#include "Core/ECS/Register.h"

#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>


class FrameBuffer;
class Project;

class Scene : public IResource
{
public :


	void Init();

	void Awake();
	void Start();


	void FixedUpdate();
	void Update();
	void LateUpdate();

	void Render();


	Entity* CreateEntity();

	Entity* GetEntities(uint32_t ID);


	template<class T>
	bool IsEntityHas(const Entity* entity);

	template<class T>
	T* TryGetComponent(const Entity* entity);

	template<class T>
	inline void AddComponent(Entity* entity)
	{
		registerScene.AddComponentInternal(T::ComponentTypeID, entity);
	}

	template<class T>
	inline T* GetComponent(Entity* entity)
	{
		return reinterpret_cast<T*>(registerScene.GetComponentInternal(T::ComponentTypeID, entity));
	}


	template<class T>
	inline void RemoveComponent(Entity* entity)
	{
		registerScene.RemoveComponentInternal(T::ComponentTypeID, entity);
	}

	inline void RemoveEntity(Entity* entity)
	{
		registerScene.RemoveEntityInternal(entity);
	}


	template<class T>
	inline void AddSystem()
	{
		registerScene.Systems.push_back(new T());
	}

	template<class T>
	inline const T* GetSystem() const 
	{
		for (IEcsSystem* system : registerScene.Systems)
		{
			const T* systemToreturn = dynamic_cast<const T*>(system);
			if(systemToreturn)
				return systemToreturn;
		}
	}


	template<class T>
	inline T* GetSystem() 
	{
		for (IEcsSystem* system : registerScene.Systems)
		{
			if (dynamic_cast<T*>(system))
				return dynamic_cast<T*>(system);
		}
	}

	template<class T>
	inline void RemoveSystem()
	{

		for (IEcsSystem* system : registerScene.Systems)
		{
			if (dynamic_cast<T*>(system))
			{
				registerScene.Systems.erase(system);
			}
		}
	}

	template<class T>
	std::vector<uint8_t>* GetComponentDataArray()
	{
		return registerScene.ComponentsData[T::ComponentTypeID].second;
	}

	std::vector<uint8_t>* GetComponentDataArray(uint32_t ID)
	{
		return registerScene.ComponentsData[ID].second;
	}

	template<class T>
	const std::vector<uint8_t>* GetComponentDataArray() const 
	{
		return registerScene.ComponentsData[T::ComponentTypeID].second;
	}

	const std::vector<uint8_t>* GetComponentDataArray(uint32_t ID) const
	{
		return registerScene.ComponentsData[ID].second;
	}

	std::string sceneName = "Scene";
	ImGuiIO io;
	const float FixedDeltatime = 0.016f;
	float  Deltatime;
	Project* currentproject;


	Scene(std::string name);
	~Scene();

private:
	Register registerScene;
};

template<class T>
inline bool Scene::IsEntityHas(const Entity* entity)
{
	uint32_t ComponentID = T::ComponentTypeID;

	if (entity->EnityComponents[ComponentID] != ComponentNULL)
		return true;

	return false;
}

template<class T>
inline T* Scene::TryGetComponent(const Entity* entity)
{
	if (!IsEntityHas<T>(entity))
		return nullptr;

	return entity->EnityComponents[T::ComponentID];
}
