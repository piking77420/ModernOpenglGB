#pragma once
#include <Collider/Collider.h>
#include "Physics/CollisionType/AABCollision.h"


class BoxCollider : public Collider
{
public:
	Vector3 mSize;
	
	void Update(Scene* scene) override;
	void ImguiWindowComponents() override;

	BoxCollider(Entity& entitytoAttach);

	BoxCollider(Entity& entitytoAttach, Vector3 zize);
	~BoxCollider();
};

