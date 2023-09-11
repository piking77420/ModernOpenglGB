#include "Core/ECS/Entity.h"
#include "Core/ECS/Component.h"
#include <atomic>
#include "Ressources/Scene/Scene.h"

void Entity::OnInspector() 
{
	
	
		for (size_t i = 0; i < EnityComponents.size(); i++)
		{
			if (EnityComponents[i] == ComponentNULL) continue;

			if (ImGui::CollapsingHeader(Component::GetComponentName(i).c_str()))
			{

				std::vector<uint8_t>* data = scene->GetComponentDataArray(i);
				Component* comp = reinterpret_cast<Component*>(&data->at(EnityComponents[i]));
				
				comp->ImguiWindowComponent();

			}


		}

		if (ImGui::CollapsingHeader("Add Component"))
		{
			for (size_t i = 0; i < Component::GetComponentTypeInfos()->size(); i++)
			{

				if (scene->HasComponent(i, this))
					continue;

				if(ImGui::Button(Component::GetComponentName(i).c_str()))
				{
					scene->AddComponent(i, this);
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

void Entity::OnDeSerialize(Scene* scene) const
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
	EnityComponents.resize(Component::GetNbrOfComponent());

	for (size_t i = 0; i < EnityComponents.size(); i++)
	{
		EnityComponents[i] = ComponentNULL;
	}
};
