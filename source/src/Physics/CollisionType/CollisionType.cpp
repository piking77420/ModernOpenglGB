#include "Physics/CollisionType/CollisionType.h"
#include "Physics/CollisionType/SphereCollision.h"
#include "Collider/SphereCollider/SphereCollider.h"





void CollisionType::IsCollided(const CollisionType& type)
{	
	Collider* currentColldier = currentTranform->GetComponent<Collider>();
	currentColldier->entitesHasBeenCollid.push_back(const_cast<Entity*>(type.currentTranform));

}

CollisionType::CollisionType() : currentTranform(nullptr)	
{
}

void CollisionType::Update(const Collider& collider)
{
}

void CollisionType::ImguiWindow()
{
}

CollisionType::CollisionType(const Entity& currentObject) : currentTranform(&currentObject)
{
}

CollisionType::~CollisionType()
{
}



