#pragma once
#include <Mathf.h>
#include "Core/DataStructure/Component/Component.h"

class Scene;
class Collider;

class Rigidbody : public Component
{
public:
	float mass;
	bool IsGravityApllied;
	Collider& collider;
	Vector3 Velocity;
	void ImguiWindowComponents() override;
	void Update(Scene* scene) override;
	Rigidbody(Entity& entity , Collider& _collide);
	~Rigidbody();

};

