#include "Physics/PhysicsSystem/PhysicsSystem.hpp"
#include "ECS/Scene.h"
#include "Physics/RigidBody/Rigidbody.h"
#include "Physics/Transform/Transform.hpp"
#include "Physics/Collider/SphereCollider.hpp"
#include "Physics/Collider/BoxCollider.hpp"
#include "EasyFunction.h"
#include "Core/AppTime.h"

void PhysicsSystem::AddForce(Rigidbody& rb, const Vector3& forces)
{
	rb.Force += forces;
}
Collider* PhysicsSystem::GetCollider(Scene* scene, uint32_t EntityID)
{
	Entity* entity = scene->GetEntities(EntityID);
	if (!entity)
	{
		LOG("This entity ID Is Unvalid", STATELOG::CRITICALERROR);
		return nullptr;
	}

	SphereCollider* sphereCollider = scene->GetComponent<SphereCollider>(entity);

	if (!sphereCollider)
	{
		BoxCollider* boxCollider = scene->GetComponent<BoxCollider>(entity);
		return &boxCollider->collider;
	}
	else
	{
		return &sphereCollider->collider;
	}

	LOG("This entity doesn't have collider Component", STATELOG::CRITICALERROR);


	return nullptr;
}



void PhysicsSystem::FixedUpdate(Scene* scene)
{
	// test Key forces 
	std::vector<Rigidbody>* rigidBodys = reinterpret_cast<std::vector<Rigidbody>*>(scene->GetComponentDataArray<Rigidbody>());

	

	ApplieGravity(scene,rigidBodys);
	//CollisionRespond(scene, rigidBodys);
	ApplieForces(scene, rigidBodys);

};



void PhysicsSystem::ApplieGravity(Scene* scene,std::vector<Rigidbody>* rigidBodys)
{
	for (size_t i = 0; i < rigidBodys->size(); i++)
	{
		Rigidbody* rigidbody = &(*rigidBodys)[i];

		if (rigidbody->IsKinematic || !rigidbody->isEnable || !rigidbody->IsGravityApplie)
			continue;

			
		PhysicsSystem::AddForce(*rigidbody, gravity * rigidbody->mass);
	}

}






void PhysicsSystem::CollisionRespond(Scene* scene, std::vector<Rigidbody>* rigidBodys)
{
	
	for (size_t i = 0; i < rigidBodys->size(); i++)
	{
		Rigidbody* rb = &(*rigidBodys)[i];
		Collider* coll = GetCollider(scene, rb->entityID);
		Entity* entity = scene->GetEntities(rb->entityID);
		Transform* transform = scene->GetComponent<Transform>(entity);

		if (coll->IsTrigger)
			return;

		for (size_t i = 0; i < coll->CollisionPoint.size(); i++)
		{
			CollisionPoint* collptr = &coll->CollisionPoint[i];
			Entity* entity = scene->GetEntities(collptr->entityIDBeenCollidWith);
			Rigidbody* rbOther = scene->GetComponent<Rigidbody>(entity);

			Vector3 Forceadded;

			if (rbOther)
			{
				Forceadded = collptr->Normal * collptr->depht * rbOther->mass;
			}
			else
			{

				Forceadded = (collptr->Normal) * (-gravity * rb->mass);
			}
			rb->Force += Forceadded;


		}

	}
}



void PhysicsSystem::UpdateDrag(Rigidbody& rb)
{
	
	//Applie dragforce
	Vector3 forcedrag = rb.Velocity;

	float dragCoefficent = forcedrag.Norm();
	float k1 = rb.drag;
	float k2 = k1 * k1;
	dragCoefficent = k1 * dragCoefficent + k2 * dragCoefficent * dragCoefficent;
	forcedrag = forcedrag.Normalize();
	forcedrag *= -dragCoefficent;
	AddForce(rb, forcedrag);

}
void PhysicsSystem::ApplieForces(Scene* scene, std::vector<Rigidbody>* rigidBodys)
{

	
	for (size_t i = 0; i < rigidBodys->size(); i++)
	{
		Rigidbody* rb = &(*rigidBodys)[i];
		Transform* transform = scene->GetComponent<Transform>(scene->GetEntities(rb->entityID));
		Collider* coll = GetCollider(scene, rb->entityID);


		if (rb->IsKinematic || !rb->isEnable)
			continue;

		constexpr float deltatime = AppTime::GetFixedDeltatime();


		Vector3 accelration = rb->Force * (1.f / rb->mass);

		// update velocity 
		rb->Velocity += accelration * deltatime;


		UpdateDrag(*rb);
		//rb->Velocity *= rb->drag;



		// make sure that if it under presision the object not moving
		for (size_t i = 0; i < Vector3::Size(); i++)
		{
			float* ptr = rb->Velocity.SetPtr() + i;
			Math::ZeroPrecision(ptr);

		}

		// update pos
		transform->pos += rb->Velocity * deltatime;

		// Reset Force
		rb->Force = Vector3::Zero();;
	}



	
}
