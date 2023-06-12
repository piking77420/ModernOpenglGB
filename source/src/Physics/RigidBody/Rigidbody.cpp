#include "Physics/RigidBody/Rigidbody.h"
#include "Core/DataStructure/Component/Collider/Collider.h"
#include "Ressources/Scene/Scene.h"
#include "Core/Input/PlayerMovement.h"

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
	bool hasTouchGround = false;	
	PlayerMovement* movement;

	if(TryGetComponent<PlayerMovement>(EntityAttachTo,&movement))
	{
		if (IsGravityApllied)	
		{

			if (!movement->IsGrounded() )//&& movement->currentState == FALLING)		
			{
				this->EntityAttachTo.transform.pos.y -= GRAVITY * scene->FixedDeltatime * mass ;
			}


		}
		
	}


}

Rigidbody::Rigidbody(Entity& entity, Collider& _collider)
	: Component(entity) , collider(_collider) , mass(1.f)
{
	m_ComponentName = "RigidBody";
}
