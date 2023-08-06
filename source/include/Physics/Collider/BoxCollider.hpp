#pragma once
#include "Core/ECS/ECSComponent.h"
#include "Collider.hpp"

class BoxCollider : public EcsComponent<BoxCollider>
{
	Collider collider;
	Vector3 Size;
};

