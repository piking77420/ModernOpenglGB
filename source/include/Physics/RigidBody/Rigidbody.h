#pragma once
#include "Core/ECS/ECSComponent.h"
#include<Math/ToolBoxMathHeaders.h>

class Scene;
class Collider;

class Rigidbody : public EcsComponent<Rigidbody>
{
public:
	bool IsKinematic = false;
	bool IsGravityApplie;

	float mass = 1.0f;
	Vector3 Force;
	Vector3 velocity;
	

};

