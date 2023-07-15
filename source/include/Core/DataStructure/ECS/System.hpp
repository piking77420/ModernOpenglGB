#pragma once
#include <vector>
#include "Core/DataStructure/ECS/Component.hpp"
class EcsSystem
{
public:
	EcsSystem(const std::vector<uint32_t>& ComponentTypeInput):componentTypes(ComponentTypeInput) {}
	virtual void UpdateComponents(float delta,BaseComponent** comp){}
	const std::vector<uint32_t>& GetTypes()
	{
		return componentTypes;
	}
private:
	std::vector<uint32_t> componentTypes;
};

