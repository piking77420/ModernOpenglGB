#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<Ressources/Shader/Shader.h>

#include<Core/Debug/Debug.h>
#include"Physics/Transform/Transform.h"
#include<Core/DataStructure/Component/Component.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>


class Component;
class AppData;
class Scene;



class Entity
{
public:

	uint32_t ID;

	std::string name;
	std::string Tag;
	Scene* scene;
	Transform transform;
	void Update(Scene* scene);
	void LateUpdate(Scene* scene);
	void PreUpdate(Scene* scene);
	void ImguiEntityWindow();
	bool HasParent();

#pragma region Components
	template<class T>
	void AddComponent(T* componentsToAdd);


	template<class T >
	// Return the Components Or NullPtr if there is no one 
	T* GetComponent() const;



	template<class T>
	void RemoveComponents();

#pragma endregion

	Entity(std::string _name, Scene* _scene);
	Entity(std::string _name, Transform _transform);
	Entity();

	~Entity();

	std::vector<Component*> Components;
private:
	static uint32_t GloblalIDs;
};

template<class T>
static bool TryGetComponent(const Entity& entity, T** returnedComponent);

#pragma region Components



template<class T>
inline void Entity::AddComponent(T* componentsToAdd)
{
	Components.push_back(componentsToAdd);
}
template<class T>
inline T* Entity::GetComponent() const
{



	for (Component* c : this->Components)
	{
		T* typedComponent = dynamic_cast<T*>(c);
		if (typedComponent != nullptr)
		{
			return typedComponent;
		}


	}

	//Debug::Log->LogWarning("There is no this component in this entity " + std::to_string(ID));

	return nullptr;
}

template<class T>
inline bool TryGetComponent(const Entity& entity, T** returnedComponent)
{


	for (Component* c : entity.Components)
	{
		T* typedComponent = dynamic_cast<T*>(c);
		if (typedComponent != nullptr)
		{
			*returnedComponent = typedComponent;
			return true;
		}


	}

	return false;
}



template<class T>
inline void Entity::RemoveComponents()
{
	for (Component* e : Components)
	{
		if (dynamic_cast<T>(e) != nullptr)
		{
			Components.erase(e);
			return;
		}
	}




}
#pragma endregion