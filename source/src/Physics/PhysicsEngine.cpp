#include "Physics/PhysicsEngine.h"
#include "Ressources/Scene/Scene.h"
/*
void PhysicsEngine::DetermianteCollision(Scene* scene)
{
	
	

	AllCollider.reserve(scene->entities.size());
	for (size_t i = 0; i < scene->entities.size(); i++)
	{
		Component* c = scene->entities[i]->GetComponent<Collider>();

		if(c)
		AllCollider.emplace_back(reinterpret_cast<Collider*>(c));
	}

	for (size_t i = 0; i < AllCollider.size(); i++)
	{
		Collider* c1 = AllCollider[i];
		for (size_t k = i + 1; k < AllCollider.size(); k++)
		{
			Collider* c2 = AllCollider[k];
			AllCollisions.push_back(CollisionDetection(c1, c2));

		}
	}
	
}

void PhysicsEngine::Update(Scene* scene)
{
	for (size_t i = 0; i < AllCollisions.size(); i++)
	{
		AllCollisions[i].collider1->GetCollsion(AllCollisions[i].collider2);
	}
}

void PhysicsEngine::Reset()
{
	AllCollider.clear();
	AllCollisions.clear();
}

*/