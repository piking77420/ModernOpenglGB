#pragma once
#include "Core/ECS/IECSSystem.h"
#include "ECS/Scene/Scene.h"


class RumicsCube : public IEcsSystem
{
public:
	ImplementIEcsSystem

	uint32_t RumicksCubeEntityId;
	Entity* Rumicube;
	RumicsCube();

	~RumicsCube();


};

