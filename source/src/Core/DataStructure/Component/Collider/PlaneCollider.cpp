#include "Core/DataStructure/Component/Collider/PlaneCollider.h"
#include "Physics/CollisionType/PlaneCollision.h"

PlaneCollider::~PlaneCollider()
{
}


PlaneCollider::PlaneCollider(Entity& entity)
{
	ID = PLANE;
	m_ComponentName = typeid(*this).name();
	CollisionShape.push_back(new PlaneCollision(entity));
}
