#pragma once
#include<ComponentsBehaviours.h>
#include <vector>
#include "LowRenderer/Gizmo/Gizmo.h"


enum class ColliderType
{
	Sphere,
	Box,
	Raycast

};


class SphereCollider;
class CollisionType;

class Collider : public Component
{
public:
	

	ColliderType Type;
	Gizmo* gizmo;
	void ImguiWindowComponents() override;
	void GetCollsion(Collider* collider);
	
	
	virtual	~Collider()
	{
		
	};
protected:
	virtual void Collision(SphereCollider* sphereCollider) {};

};

