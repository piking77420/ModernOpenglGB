#pragma once
#include "Core/ECS/IECSSystem.h"
#include "Ressources/Scene/Scene.h"


class RumicsCube : public IEcsSystem
{
public:
	ImplementIEcsSystem

	uint32_t RumicksCubeEntityId;

	RumicsCube();

	~RumicsCube();


};

