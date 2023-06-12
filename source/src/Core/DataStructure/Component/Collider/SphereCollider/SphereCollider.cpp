#include "Collider/SphereCollider/SphereCollider.h"
#include "Physics/CollisionType/SphereCollision.h"
#include "LowRenderer/RendererComponent/GizmoRenderer/Gizmo/Sphere/SphereGizmo.h"






SphereCollider::SphereCollider(Entity& entity) : Collider(entity) ,   radius(1.f)
{
	ID = SPHERE;
	this->m_ComponentName = "SphereCollider";
	CollisionShape.push_back(new SphereCollision(EntityAttachTo,this->radius));
	Gizmorenderer = new SphereGizmo(EntityAttachTo,this->radius);
}

SphereCollider::SphereCollider(Entity& entity, float radius) : Collider(entity) 
{	
	ID = SPHERE;
	this->m_ComponentName = "SphereCollider";
	this->radius = radius;
	CollisionShape.push_back(new SphereCollision(EntityAttachTo, this->radius));
	Gizmorenderer = new SphereGizmo(entity, this->radius);

}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::ImguiWindowComponents()
{
	ImGui::DragFloat("radius", &radius);
	ImGui::Checkbox("Is Collided", &isCollided);
	if (Gizmorenderer != nullptr)
		ImGui::Checkbox("Drawing Gizmo", &Gizmorenderer->IsDrawing);

}