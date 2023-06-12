#pragma once

#include "Core/DataStructure/Component/Component.h"
#include "Physics/RigidBody/Rigidbody.h"

#include <Mathf.h> 

class Scene;


enum PlayerState
{
	IDLE,MOVE,JUMPING,FALLING
};


class PlayerMovement : public Component
{
public:
	PlayerState currentState;
	Rigidbody* rb;
	bool isGrounded;
	float Friction;
	float Speed;
	float PlayerJumpStrengt;
	float GravityMultiplier;
	float OnAirSlow;
	Vector3 acceleration;
	Vector3 Velocity;
	Vector3 JumpVelocity;

	float timerIsGrounded = 0.5;
	void ImguiWindowComponents() override;
	void PlayerMovment(Scene* scene);
	void Update(Scene* scene) override;

	void  PlayerJump(Scene* scene);
	bool IsGrounded();
	void AirControl();
	PlayerMovement(Entity& entity);

private :
	float mBaseSpeed;
	float LastY;
	GLFWwindow*  currentContext;
	void CheckIfFalling();

};

