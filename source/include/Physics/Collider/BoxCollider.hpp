#pragma once
#include "Core/ECS/ECSComponent.h"
#include "Collider.hpp"

class BoxCollider : public EcsComponent<BoxCollider>
{
public:
	Collider collider;
	Vector3 Size = Vector3::One();
	void ImguiWindowComponent() override;

};

