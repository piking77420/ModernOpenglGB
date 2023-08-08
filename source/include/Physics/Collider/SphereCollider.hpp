#pragma once
#include "Core/ECS/ECSComponent.h"
#include "Collider.hpp"


class SphereCollider : public EcsComponent<SphereCollider>
{
public:
	Collider collider;
	float radius = 1.f;
	 void ImguiWindowComponent() override;

};

