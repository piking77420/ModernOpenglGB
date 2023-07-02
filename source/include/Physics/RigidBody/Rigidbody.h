#pragma once
#include <Mathf.h>
#include "Core/DataStructure/Component/Component.h"

class Scene;
class Collider;

class Rigidbody : public Component
{
public:
	void FixedUpdate(Scene* scene) override;
	void ImguiWindowComponents() override;
	float mass;
	bool IsGravityApllied;
	Vector3 Velocity;
	Rigidbody();
	~Rigidbody();
private :
	Collider& collider;
};

