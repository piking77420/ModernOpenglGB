#pragma once

#include "Core/DataStructure/ECS/Component.hpp"
#include "Core/DataStructure/ECS/System.hpp"
#include "Core/DataStructure/ECS/Entity.hpp"
#include <map>

class EntityComponentSystem
{
public:
	EntityComponentSystem() {};
	~EntityComponentSystem();

	// EntitesMethod
	void AddEntities(BaseComponent* Entitycomponents, const uint32_t* componentsIds, size_t nbrOfComponents);
	
	template<typename Components>
	void AddComponent(Entity* entity)
	{
		InternalAddComponent(entity, Components::ID);
	}
	

private:

	// Ok 
	std::vector<EcsSystem*> mSystems;

	// First int pair is the index of the entities
	std::vector<Entity>* entities = new std::vector<Entity>();

	
	inline void InternalAddComponent(Entity* entity,uint32_t componentsId);
};

