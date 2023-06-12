#pragma once
#include "Mathf.h"
#include "Core/DataStructure/Entity/Entity.h"

class Collider;

class CollisionType
{
public:
	const Entity* currentTranform;

	void IsCollided(const CollisionType& type);
	CollisionType();
	virtual void Update(const Collider& collider);
	virtual void ImguiWindow();
	CollisionType(const Entity& currentObject);
	virtual ~CollisionType();

protected:


};
