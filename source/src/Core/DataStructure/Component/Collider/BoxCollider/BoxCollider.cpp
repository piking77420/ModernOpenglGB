#include "Collider/BoxCollider/BoxCollider.h"

void BoxCollider::Update(Scene* scene)
{

}

void BoxCollider::ImguiWindowComponents()
{
	ImGui::DragFloat3("Size", mSize.SetPtr());

}

void BoxCollider::Collision(SphereCollider* sphereCollider)
{

}

BoxCollider::BoxCollider() : mSize(EntityAttachTo->transform.GetScale())
{
	Type = ColliderType::Box;
	m_ComponentName = "BOX COLLIDER";
}

BoxCollider::BoxCollider(Vector3 size) :  mSize(size)
{
	Type = ColliderType::Box;
	m_ComponentName = "BOX COLLIDER";
}

BoxCollider::~BoxCollider()
{
}


