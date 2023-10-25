#include "Core/ECS/Register.h"
#include "Physics/Transform/Transform.hpp"
#include "Physics/GraphScene/GraphScene.h"
#include "Core/Debug/Debug.h"



Register::Register()
{
	if (Component::m_componentTypeInfos == nullptr)
		Component::m_componentTypeInfos = new std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t, std::string> >();


	for (size_t i = 0; i < Component::GetNbrOfComponent(); i++)
	{
		std::pair<uint32_t, std::vector<uint8_t>*> newArray((uint32_t)i, new std::vector<uint8_t>());
		ComponentsData.push_back(newArray);
		
	}


}

Register::~Register()
{
	// We don't have to call The destructor due to end of the app
	for (size_t i = 0; i < ComponentsData.size(); i++)
	{
		delete ComponentsData[i].second;
	}
	ComponentsData.clear();
	for (size_t i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}

	for (size_t i = 0; i < systems.size(); i++)
	{
		delete systems[i];
	}



}

void Register::AddComponentInternal(uint32_t ComponenTypeID, Entity* entity)
{
	for (size_t i = 0; i < ComponentsData.size(); i++)
	{
		if (ComponentsData[i].first == ComponenTypeID)
		{
			size_t sizeOfComponent = Component::GetSizeOfComponent(ComponenTypeID);
			std::vector<uint8_t>& data = *ComponentsData[i].second;
			ECSComponentCreateFunction createfn = Component::GetCreateFN(ComponenTypeID);
			Component* ptr = nullptr;
			uint32_t index = createfn(data, entity, &ptr);
			AddComponentEntity(entity, ComponenTypeID, index);

			// On Resize 
			TriggerOnresizeDataEvent(ComponenTypeID, &data);

			return;
		}
	}
}

Component* Register::GetComponentInternal(uint32_t ComponenTypeID, Entity* entity)
{
	uint32_t IndexOffComponent = entity->entityComponents.at(ComponenTypeID);
	// this entities Doesnt' have this Component
	if (IndexOffComponent == ComponentNULL)
		return nullptr;

	Component* ptr = reinterpret_cast<Component*>(&ComponentsData.at(ComponenTypeID).second->at(IndexOffComponent));

	return ptr;
}



const Component* Register::GetComponentInternal(uint32_t ComponenTypeID, const Entity* entity) const
{
	uint32_t IndexOffComponent = entity->entityComponents.at(ComponenTypeID);
	// this entities Doesnt' have this Component
	if (IndexOffComponent == ComponentNULL)
		return nullptr;

	const Component* ptr = reinterpret_cast<const Component*>(&ComponentsData.at(ComponenTypeID).second->at(IndexOffComponent));

	return ptr;
}

Entity* Register::GetEntiesById(uint32_t entityId)
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i]->GetID() == entityId)
			return entities[i];
	}
	return nullptr;
}


void Register::RemoveComponentInternal(uint32_t componentTypeID, Entity* entity)
{

	if (componentTypeID == Transform::componentTypeID)
		return;

	if (entity->entityComponents.at(componentTypeID) == ComponentNULL)
	{
		// This entity Doesn'h have this Component
		return;
	}
	uint32_t index = entity->entityComponents.at(componentTypeID);

	std::vector<uint8_t>& dataArray = *ComponentsData.at(componentTypeID).second;
	ECSComponentFreeFunction freefn = Component::GetFreeFN(componentTypeID);
	size_t sizeOfComponent = Component::GetSizeOfComponent(componentTypeID);

	//Last index for last Componenet
	uint32_t lastIndex = (uint32_t)(dataArray.size() - sizeOfComponent);

	Component* destComp = reinterpret_cast<Component*>(&dataArray[index]);
	Component* lastComp = reinterpret_cast<Component*>(&dataArray[lastIndex]);
	freefn(destComp);

	// the Component Free was the last so just resize it 
	if (index == lastIndex) {
		dataArray.resize(lastIndex);
		RemoveComponentEntity(entity, componentTypeID);
		TriggerOnresizeDataEvent(componentTypeID, &dataArray);
		return;
	}


	Entity* entitylast = nullptr;
	entitylast = GetEntiesById(lastComp->entityID);

	if (entitylast == nullptr)
		throw std::runtime_error("Entity not found for lastComp->entityID");


	memcpy(destComp, lastComp, sizeOfComponent);
	
	entitylast->entityComponents.at(componentTypeID) = index;
	dataArray.resize(lastIndex);

	RemoveComponentEntity(entity, componentTypeID);

	TriggerOnresizeDataEvent(componentTypeID, &dataArray);
	
}



void Register::RemoveEntityInternal(Entity* entity)
{
	for (uint32_t i = 0; i < entity->entityComponents.size(); i++)
	{
		RemoveComponentInternal(i, entity);
	}


	uint32_t destIndex = entity->GetID();

	uint32_t srcIndex = (uint32_t)entities.size() - 1;

	delete entities[destIndex];


	// Care
	entities[destIndex] = entities[srcIndex];



	entities.pop_back();
}



void Register::AddComponentEntity(Entity* entity, uint32_t componentTypeID, uint32_t componentIndex)
{
	// we assume that all arrays has been initialised

	// if it's empty just add 
	if (entity->entityComponents.at(componentTypeID) == ComponentNULL)
	{
		entity->entityComponents.at(componentTypeID) = componentIndex;
	}

	// This entity doesn't already has this component
	return;

}

void Register::RemoveComponentEntity(Entity* entity, uint32_t componentTypeID)
{
	entity->entityComponents.at(componentTypeID) = ComponentNULL;
}

void Register::AddSystemInternal(IEcsSystem* system)
{
	systems.push_back(system);
	OnReSizeDataVector.push_back(&IEcsSystem::OnResizeData);
}

void Register::TriggerOnresizeDataEvent(uint32_t componentTypeID, std::vector<uint8_t>* data)
{
	for (size_t i = 0; i < OnReSizeDataVector.size(); i++)
	{
		OnReSizeDataVector[i](*systems[i], componentTypeID, data);
	}

}


