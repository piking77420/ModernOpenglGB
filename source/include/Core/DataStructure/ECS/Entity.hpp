#pragma once

#include "Core/DataStructure/ECS/Component.hpp"
#include <vector>

class Entity
{
public:

	uint32_t EntitesId;
	// 1nd int is the Component id > TYPE
	// 2nd is the components which id of the current Type it is
	std::map<uint32_t, std::vector<BaseComponent*>> ComponentsData;
	Entity();
	~Entity(){};

private:

};	

