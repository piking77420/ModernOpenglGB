#pragma once
#include "Core/ECS/ECSComponent.h"
#include<Math/ToolBoxMathHeaders.h>
#include "Physics/Transform/Transform.hpp"
class Scene;
class Collider;

class Rigidbody : public EcsComponent<Rigidbody>
{
public:
	bool IsKinematic = false;
	bool IsGravityApplie = true;

	Vector3 angularVelocity = Vector3::Zero();

	float mass = 1.0f;


	Vector3 Force = Vector3::Zero();
	Vector3 Velocity = Vector3::Zero();
	
	void ImguiWindowComponent() override;
private:
};

