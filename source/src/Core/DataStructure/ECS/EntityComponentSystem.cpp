#include "Core/DataStructure/ECS/EntityComponentSystem.hpp"
#include "Core/Debug/Debug.h"

EntityComponentSystem::~EntityComponentSystem()
{

}

void EntityComponentSystem::AddEntities(BaseComponent* Entitycomponents, const uint32_t* componentsIDs, size_t nbrOfComponents)
{
	

}

inline void EntityComponentSystem::InternalAddComponent(Entity* entity, uint32_t componentsId)
{
	if (!BaseComponent::IsValid(componentsId)) {
		Debug::Log->LogWarning("Not valid Component");
	}

	ECSComponentCreateFunction createfun = BaseComponent::GetCreateFunction(componentsId);

	bool hasThisType;
	for (auto it = entity->ComponentsData.begin(); it < entity->ComponentsData.end(); it++)
	{

	}

	createfun()

}

