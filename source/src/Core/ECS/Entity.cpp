#include "Core/ECS/Entity.h"
#include "Core/ECS/Component.h"
#include <atomic>
#include "ECS/Scene.h"







void Entity::OnSerialize(Scene* scene) const
{

	for (uint32_t i = 0; i < Component::GetNbrOfComponent(); i++)
	{
		if (!scene->HasComponent(i, this))
			continue;


		std::vector<uint8_t>* data = scene->GetComponentDataArray(i);



		for (uint32_t k = 0; k < data->size() / Component::GetSizeOfComponent(i); k++)
		{
			Component* ptr = reinterpret_cast<Component*> (&data->at(k));

			if (ptr->entityID == ID)
			{
				ptr->OnSerialize(scene);
			}
		}

	}

}

void Entity::OnDeSerialize(Scene* scene) 
{
	for (uint32_t i = 0; i < Component::GetNbrOfComponent(); i++)
	{
		if (!scene->HasComponent(i, this))
			continue;


		std::vector<uint8_t>* data = scene->GetComponentDataArray(i);



		for (uint32_t k = 0; k < data->size() / Component::GetSizeOfComponent(i); k++)
		{
			Component* ptr = reinterpret_cast<Component*> (&data->at(k));

			if (ptr->entityID == ID)
			{
				ptr->OnDeSerialize(scene);
			}
		}

	}

}

Entity::Entity()
{
	entityComponents.resize(Component::GetNbrOfComponent());

	for (uint32_t i = 0; i < entityComponents.size(); i++)
	{
		entityComponents[i] = ComponentNULL;
	}
};
