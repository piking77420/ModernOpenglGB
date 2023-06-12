#include "Core/Input/PlayerMovement.h"
#include "Ressources/Scene/Scene.h"
#include <External/GLFW/glfw3.h>
#include "Physics/RigidBody/Rigidbody.h"
#include "Collider/Collider.h"

#define STRENGHT_CONTSTANT_MULTIPLIER 30


void PlayerMovement::ImguiWindowComponents()
{

	ImGui::BeginDisabled(true);
	ImGui::Checkbox("IsGrounded", &isGrounded);
	ImGui::EndDisabled();
	ImGui::DragFloat("Jumpstrenght", &PlayerJumpStrengt);
	ImGui::DragFloat("Speed", &Speed);
	ImGui::SliderFloat("Friction", &Friction,0,2);
	ImGui::SliderFloat("GraviityMultiplier", &GravityMultiplier, 0, 30);
	ImGui::Text( ( "State  = " + std::to_string(currentState)).c_str() ) ;


}

void PlayerMovement::PlayerMovment(Scene* scene)
{
	float vel = scene->FixedDeltatime * Speed;

	Velocity = Velocity/Friction;

	if (glfwGetKey(currentContext, GLFW_KEY_W) == GLFW_PRESS)
	{
		Velocity += Vector3::Forward * acceleration.x;
	}

	if (glfwGetKey(currentContext, GLFW_KEY_S) == GLFW_PRESS)
	{
		Velocity += Vector3::BackForward * acceleration.x;;
	}

	if (glfwGetKey(currentContext, GLFW_KEY_A) == GLFW_PRESS)
	{
		Velocity += Vector3::Left * acceleration.x;
	}

	if (glfwGetKey(currentContext, GLFW_KEY_D) == GLFW_PRESS)
	{
		Velocity += Vector3::Right * acceleration.x;
	}

	if(Velocity.Norm() > 0.5f && isGrounded)
	{
		currentState = MOVE;
	}



	Vector3 pos = EntityAttachTo.GetComponent<Transform>()->pos;
	Vector3 newpos = pos + (Velocity * vel);

	EntityAttachTo.GetComponent<Transform>()->pos.x = Lerp(pos, newpos, 0.04f).x;
	EntityAttachTo.GetComponent<Transform>()->pos.z = Lerp(pos, newpos, 0.04f).z;

	

}



void PlayerMovement::Update(Scene* scene)
{
	currentContext = glfwGetCurrentContext();
	
	PlayerJump(scene);
	PlayerMovment(scene);
	AirControl();



}
void PlayerMovement::PlayerJump(Scene* scene)	
{
	isGrounded = IsGrounded();

	if (Velocity.Norm() <= 0.3f && JumpVelocity.Norm() <= 0.3f && IsGrounded())
		currentState = IDLE;


	Transform* transform = EntityAttachTo.GetComponent<Transform>();
	if (glfwGetKey(currentContext, GLFW_KEY_SPACE) == GLFW_PRESS && isGrounded)
	{
		currentState = JUMPING;

		JumpVelocity += Vector3::Up * PlayerJumpStrengt * scene->FixedDeltatime * GRAVITY ;
		isGrounded = false;

	}

	if (currentState == JUMPING)
	{
		JumpVelocity = JumpVelocity / Friction;
		Vector3 TargetPos = transform->pos + JumpVelocity ;
		EntityAttachTo.GetComponent<Transform>()->pos.y = Lerp(transform->pos, TargetPos, 0.02f).y;
		CheckIfFalling();

	}

	if (currentState == FALLING)
	{
		transform->pos.y -= GravityMultiplier * scene->io->DeltaTime;
		isGrounded = IsGrounded();

	}


}

PlayerMovement::PlayerMovement(Entity& entity) : Component(entity)
{
	m_ComponentName = "PlayerMovement";
	currentContext = glfwGetCurrentContext();
	Speed = 2;
	PlayerJumpStrengt = 165;
	Friction = 1.025;
	GravityMultiplier = 22;
	OnAirSlow = 0.75f;
	acceleration = Vector3(2, 5, 2);
	currentState = IDLE;
	mBaseSpeed = Speed;
	rb = entity.GetComponent<Rigidbody>();

}

bool PlayerMovement::IsGrounded()
{
	Collider* collider = EntityAttachTo.GetComponent<Collider>();

	for (size_t i = 0; i < collider->entitesHasBeenCollid.size(); i++)
	{
		if (collider->entitesHasBeenCollid[i]->Tag == "Ground")
		{
			return  true;
		}
		else
		{
			return  false;
		}
	}


	return false;
}

void PlayerMovement::AirControl()
{
	if(currentState == JUMPING || currentState == FALLING)
	{
		Speed = OnAirSlow;
	}
	

	if(isGrounded)
	{
		Speed = mBaseSpeed;
	}
}

void PlayerMovement::CheckIfFalling()
{
	Transform* transform = EntityAttachTo.GetComponent<Transform>();


		if (LastY < transform->pos.y)
		{
			LastY = transform->pos.y;
		}
		else
		{
			JumpVelocity = Vector3::Zero;
			currentState = FALLING;
			LastY = -INFINITY;
		}

	
}
