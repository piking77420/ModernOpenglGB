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



void Rigidbody::FixedUpdate(Scene* scene)
{
	


}

Rigidbody::Rigidbody()
	:  collider(*EntityAttachTo->GetComponent<Collider>()) , mass(1.f)
{
	m_ComponentName = "RigidBody";
}
