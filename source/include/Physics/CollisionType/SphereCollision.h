#pragma once
#include "Physics/CollisionType/CollisionType.h"

class SphereCollision : public CollisionType
{
public:


	float& radius;


	SphereCollision(const Entity& currentObject, float& _radius);
	~SphereCollision();
private:
	// All collision Support // 
	void ImguiWindow() override;

};

