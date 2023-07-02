#include "Core/DataStructure/Component/Collider/Collider.h"
#include "Collider/SphereCollider/SphereCollider.h"







void Collider::ImguiWindowComponents()
{

}

void Collider::GetCollsion(Collider* collider)
{
	switch (collider->Type)
	{
	default:
		break;

	case ColliderType::Sphere:
		SphereCollider* Sphere = reinterpret_cast<SphereCollider*>(collider);
		Collision(Sphere);
			break;
	}


}


