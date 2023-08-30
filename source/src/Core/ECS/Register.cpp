#include "Core/ECS/Register.h"
#include "Physics/Transform/Transform.hpp"
#include "Physics/GraphScene/GraphScene.h"
#include "Core/Debug/Debug.h"



Register::Register()
{
	for (size_t i = 0; i < Component::GetNbrOfComponent(); i++)
	{
		std::pair<uint32_t, std::vector<uint8_t>*> newArray(i, new std::vector<uint8_t>());
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
			AddComponentEntitie(entity, ComponenTypeID, index);

			// On Resize 
			TriggerOnresizeDataEvent(ComponenTypeID, &data);

			return;
		}
	}
}

Component* Register::GetComponentInternal(uint32_t ComponenTypeID, Entity* entity)
{
	uint32_t IndexOffComponent = entity->EnityComponents.at(ComponenTypeID);
	// this entities Doesnt' have this Component
	if (IndexOffComponent == ComponentNULL)
		return nullptr;
	Component* ptr = reinterpret_cast<Component*>(&ComponentsData.at(ComponenTypeID).second->at(IndexOffComponent));

	return ptr;
}



const Component* Register::GetComponentInternal(uint32_t ComponenTypeID, const Entity* entity) const
{
	uint32_t IndexOffComponent = entity->EnityComponents.at(ComponenTypeID);
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
}


void Register::RemoveComponentInternal(uint32_t ComponenTypeID, Entity* entity)
{

	if (ComponenTypeID == Transform::ComponentTypeID)
		return;

	if (entity->EnityComponents.at(ComponenTypeID) == ComponentNULL)
	{
		// This entity Doesn'h have this Component
		return;
	}
	uint32_t index = entity->EnityComponents.at(ComponenTypeID);

	std::vector<uint8_t>& dataArray = *ComponentsData.at(ComponenTypeID).second;
	ECSComponentFreeFunction freefn = Component::GetFreeFN(ComponenTypeID);
	size_t SizeOfComponent = Component::GetSizeOfComponent(ComponenTypeID);

	//Last index for last Componenet
	uint32_t LastIndex = dataArray.size() - SizeOfComponent;

	Component* destComp = reinterpret_cast<Component*>(&dataArray[index]);
	Component* LastComp = reinterpret_cast<Component*>(&dataArray[LastIndex]);
	freefn(destComp);

	// the Component Free was the last so just resize it 
	if (index == LastIndex) {
		dataArray.resize(LastIndex);
		RemoveComponentEntitie(entity, ComponenTypeID);
		TriggerOnresizeDataEvent(ComponenTypeID, &dataArray);
		return;
	}

	memcpy(destComp, LastComp, SizeOfComponent);
	Entity* entitylast = GetEntiesById(LastComp->entityID);
	entitylast->EnityComponents.at(ComponenTypeID) = index;
	dataArray.resize(LastIndex);

	RemoveComponentEntitie(entity, ComponenTypeID);

	TriggerOnresizeDataEvent(ComponenTypeID, &dataArray);

	
}



void Register::RemoveEntityInternal(Entity* entity)
{
	for (size_t i = 0; i < entity->EnityComponents.size(); i++)
	{
		RemoveComponentInternal(i, entity);
	}


	uint32_t destIndex = entity->GetID();

	uint32_t srcIndex = entities.size() - 1;

	delete entities[destIndex];


	// Care
	entities[destIndex] = entities[srcIndex];



	entities.pop_back();
}



void Register::AddComponentEntitie(Entity* entity, uint32_t ComponenTypeID, uint32_t ComponentIndex)
{
	// we assume There is alrealy all Array has been initialise


	// if it's empty just add 
	if (entity->EnityComponents.at(ComponenTypeID) == ComponentNULL)
	{
		entity->EnityComponents.at(ComponenTypeID) = ComponentIndex;
	}

	// This entities Doest Alrealy has This Compoennt
	return;

}

void Register::RemoveComponentEntitie(Entity* entity, uint32_t ComponenTypeID)
{
	entity->EnityComponents.at(ComponenTypeID) = ComponentNULL;
}

void Register::AddSystemInternal(IEcsSystem* system)
{
	Systems.push_back(system);
	OnReSizeDataVector.push_back(&IEcsSystem::OnResizeData);
}

void Register::TriggerOnresizeDataEvent(uint32_t ComponenTypeID, std::vector<uint8_t>* data)
{
	for (size_t i = 0; i < OnReSizeDataVector.size(); i++)
	{
		OnReSizeDataVector[i](*Systems[i], ComponenTypeID, data);
	}

}


