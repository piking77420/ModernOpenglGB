#pragma once
#include <Collider/Collider.h>

class SphereCollider;

class BoxCollider : public Collider
{
public:
	Vector3 mSize;
	
	void Update(Scene* scene) override;
	void ImguiWindowComponents() override;
	void Collision(SphereCollider* sphereCollider) override;

	BoxCollider();

	BoxCollider( Vector3 zize);
	~BoxCollider();
};

