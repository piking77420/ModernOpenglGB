#include "Physics/PhysicsSystem/PhysicsSystem.hpp"
#include "Ressources/Scene/Scene.h"
#include "Physics/RigidBody/Rigidbody.h"
#include "Physics/Transform/Transform.hpp"
float PhysicsSystem::FixedDelatime = 0;


void PhysicsSystem::Init(Scene* scene)
{
	PhysicsSystem::FixedDelatime = scene->FixedDeltatime;
};

void PhysicsSystem::Awake(Scene* scene)
{

};
void PhysicsSystem::Start(Scene* scene)
{

};
void PhysicsSystem::OnDrawGizmo(Scene* scene)
{

};

void PhysicsSystem::FixedUpdate(Scene* scene)
{
	std::vector<Rigidbody>* rigidBodys = reinterpret_cast<std::vector<Rigidbody>*>(scene->GetComponentDataArray<Rigidbody>());
	ApplieGravity(scene,rigidBodys);
	


};
void PhysicsSystem::Update(Scene* scene)
{

};
void PhysicsSystem::LateUpdate(Scene* scene)
{

};

void PhysicsSystem::Render(Shader& shader, Scene* scene)
{

};
void PhysicsSystem::OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data)
{

};

void PhysicsSystem::ApplieGravity(Scene* scene,std::vector<Rigidbody>* rigidBodys)
{
	for (size_t i = 0; i < rigidBodys->size(); i++)
	{
		Rigidbody* rigidbody = &(*rigidBodys)[i];

		rigidbody->Force += rigidbody->mass * Gravity;
		rigidbody->velocity += rigidbody->Force / rigidbody->mass * FixedDelatime;
		Entity* ent = scene->GetEntities(rigidbody->entityID);
		Transform* transform = scene->GetComponent<Transform>(ent);
		transform->pos += rigidbody->velocity * FixedDelatime;

		rigidbody->Force = Vector3::Zero();
	}

}
