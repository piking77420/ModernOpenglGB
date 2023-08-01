#include "Core/ECS/Entity.h"
#include "Core/ECS/Component.h"



Entity::Entity()
{
	EnityComponents.resize(Component::GetNbrOfComponent());
};
