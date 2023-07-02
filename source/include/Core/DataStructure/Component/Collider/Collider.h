#pragma once
#include<ComponentsBehaviours.h>
#include <vector>


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
	void ImguiWindowComponents() override;
	void GetCollsion(Collider* collider);
	
	
	virtual	~Collider()
	{
		
	};
protected:
	virtual void Collision(SphereCollider* sphereCollider) {};

};

