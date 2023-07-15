#include "Core/DataStructure/ECS/Component.hpp"
#include "Core/DataStructure/ECS/Entity.hpp"

// static uint32_t componentID = 0;
/*
uint32_t BaseComponent::NextId()
{
	return componentID++;
}
*/

 std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>> BaseComponent::componentsType;

uint32_t BaseComponent::Register(ECSComponentCreateFunction create, ECSComponentFreeFunction free, size_t size)
{  
	uint32_t Componentid = componentsType.size();
	componentsType.push_back(std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>(create, free, size));
	return Componentid;
}
