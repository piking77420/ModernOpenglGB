#pragma once
#include<vector>
#include "Physics/CollisionType/SphereCollision.h"
#include "Physics/CollisionType/PlaneCollision.h"
#include"Physics/CollisionType/AABCollision.h"
#include "Physics/CollisionType/BoxCollisionType.h"
class Collider;



struct CollisionDetection
{
	Collider* collider1;
	Collider* collider2;


};


class PhysicsEngine
{
public:

	std::vector<Collider*> allCollider;
	std::vector<CollisionDetection> AllCollisions;


	//std::vector<Collider*> allColliderUi;
	//std::vector<CollisionDetection> AllCollisionsUi;

	void DeterminateNbrOfCollision();
	void UpdateColliders();

	

	PhysicsEngine();
	~PhysicsEngine();


private: 
	void UpdatePhysics();
	void UpdateUi();
	void CheckCollision(SphereCollision* sphere1, AABCollision* quad1);
	void CheckCollision(SphereCollision* sphere1, SphereCollision* sphere2);
	void CheckCollision(PlaneCollision* sphere1, PlaneCollision* sphere2);
	void CheckCollision(SphereCollision* sphere1, PlaneCollision* plane1);


	void CheckCollision(SphereCollision* sphere1, BoxCollisionType* box1);
	void CheckCollision(AABCollision* sphere1, BoxCollisionType* quad1);



};

