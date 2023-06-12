#include "Physics/RigidBody/Rigidbody.h"
#include "Core/DataStructure/Component/Collider/Collider.h"
#include "Ressources/Scene/Scene.h"

Rigidbody::~Rigidbody()
{
}


void Rigidbody::ImguiWindowComponents()
{
	ImGui::Checkbox("IsGravityApllied", &IsGravityApllied);
	ImGui::DragFloat("Mass", &mass);

}



void Rigidbody::Update(Scene* scene)
{
	


}

Rigidbody::Rigidbody(Entity& entity, Collider& _collider)
	:  collider(_collider) , mass(1.f)
{
	m_ComponentName = "RigidBody";
}
