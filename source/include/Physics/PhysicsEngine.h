#pragma once
#include<vector>
class Collider;




struct CollisionDetection
{
	Collider* collider1;
	Collider* collider2;


};

class Scene;

class PhysicsEngine
{
public:

	void DetermianteCollision(Scene* scene);
	void Update(Scene* scene);
	void Reset();

	PhysicsEngine(){};
	~PhysicsEngine(){};


private: 
	std::vector<Collider*> AllCollider;
	std::vector<CollisionDetection> AllCollisions;


};

