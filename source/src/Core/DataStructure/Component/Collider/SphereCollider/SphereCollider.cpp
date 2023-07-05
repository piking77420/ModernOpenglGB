#include "Collider/SphereCollider/SphereCollider.h"
#include "LowRenderer/Gizmo/GizmoCollider/SphereGizmoCollider.h"





void SphereCollider::Collision(SphereCollider* sphereCollider)
{

	

	Vector3 selftPos = this->EntityAttachTo->transform.GetWordlPos();
	Vector3 otherspherepos = sphereCollider->EntityAttachTo->transform.GetWordlPos();

	float distance = (otherspherepos - selftPos).Norm();

	float r1r2 = this->radius + sphereCollider->radius;
	if (distance < r1r2)
	{
		//Debug::Log->LogTODO("Collide");
	}



}

SphereCollider::SphereCollider() : radius(1.f)
{
	gizmo = new SphereGizmoCollider(this);
	Type = ColliderType::Sphere;
	m_ComponentName = "Sphere Collider";
}

SphereCollider::SphereCollider(float radius) : radius(radius)
{	
	gizmo = new SphereGizmoCollider(this);
	Type = ColliderType::Sphere;
	m_ComponentName = "Sphere Collider";
}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::ImguiWindowComponents()
{
	ImGui::SliderFloat("Radius", &radius, 0, 100);

}