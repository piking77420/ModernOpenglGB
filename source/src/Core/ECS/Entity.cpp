#include "Core/ECS/Entity.h"
#include "Core/ECS/Component.h"
#include <atomic>
#include "ECS/Scene/Scene.h"

void Entity::OnInspector(uint32_t entityID , Scene* scene) 
{
	Entity* ent = scene->GetEntities(entityID);

	
		for (size_t i = 0; i < ent->entityComponents.size(); i++)
		{
			if (ent->entityComponents[i] == ComponentNULL) continue;

			if (ImGui::CollapsingHeader(Component::GetComponentName(i).c_str()))
			{

				std::vector<uint8_t>* data = scene->GetComponentDataArray(i);
				Component* comp = reinterpret_cast<Component*>(&data->at(ent->entityComponents[i]));
				
				comp->ImguiWindowComponent();

			}


		}

		if (ImGui::CollapsingHeader("Add Component"))
		{
			for (size_t i = 0; i < Component::GetComponentTypeInfos()->size(); i++)
			{

				if (scene->HasComponent(i, ent))
					continue;

				if(ImGui::Button(Component::GetComponentName(i).c_str()))
				{
					scene->AddComponent(i, ent);
				}

			}


		}

	

}

void Entity::OnSerialize(Scene* scene) const
{

	for (size_t i = 0; i < Component::GetNbrOfComponent(); i++)
	{
		if (!scene->HasComponent(i, this))
			continue;


		std::vector<uint8_t>* data = scene->GetComponentDataArray(i);



		for (size_t k = 0; k < data->size() / Component::GetSizeOfComponent(i); k++)
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
	for (size_t i = 0; i < Component::GetNbrOfComponent(); i++)
	{
		if (!scene->HasComponent(i, this))
			continue;


		std::vector<uint8_t>* data = scene->GetComponentDataArray(i);

		

		for (size_t k = 0; k < data->size() / Component::GetSizeOfComponent(i); k++)
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

	for (size_t i = 0; i < entityComponents.size(); i++)
	{
		entityComponents[i] = ComponentNULL;
	}
};
