#include "Core/ECS/Entity.h"
#include "Core/ECS/Component.h"

#include "Ressources/Scene/Scene.h"

void Entity::OnInspector()
{

	
	for (size_t i = 0; i < EnityComponents.size(); i++)
	{
		if(EnityComponents[i] != ComponentNULL)
		{
			std::vector<uint8_t>* data = scene->GetComponentDataArray(i);
			Component* comp = reinterpret_cast<Component*>(&data->at(EnityComponents[i]));
			comp->ImguiWindowComponent();

			
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
