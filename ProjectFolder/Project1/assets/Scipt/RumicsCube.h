#pragma once
#include "Core/ECS/IECSSystem.h"
#include "ECS/Scene.h"


class RumicsCube : public IEcsSystem
{
public:
	void Init(Scene* scene) override;
	void Update(Scene* scene) override;

	uint32_t RumicksCubeEntityId;
	Entity* Rumicube;
	RumicsCube();

	~RumicsCube();


};

