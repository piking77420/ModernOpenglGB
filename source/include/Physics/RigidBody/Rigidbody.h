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
	float mass = 1.0f;
	float drag = 0.99f;
	Vector3 Velocity = Vector3::Zero();
	Vector3 Force = Vector3::Zero();
	void ImguiWindowComponent() override;
private:

};

