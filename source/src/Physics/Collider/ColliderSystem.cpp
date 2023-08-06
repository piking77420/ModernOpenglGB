#include <vector>
#include "Physics/Collider/ColliderSystem.hpp"
#include "Physics/Collider/SphereCollider.hpp"
#include "Physics/Collider/BoxCollider.hpp"
#include "Ressources/Scene/Scene.h"
#include "Physics/Transform/Transform.hpp"
#include "Core/DataStructure/Project.hpp"


void ColliderSystem::Init(Scene* scene)
{
}

void ColliderSystem::Awake(Scene* scene)
{
	currentScene = scene;
}

void ColliderSystem::Start(Scene* scene)
{
}

void ColliderSystem::FixedUpdate(Scene* scene)
{
	std::vector<SphereCollider>* dataSphere =  reinterpret_cast<std::vector<SphereCollider>*>(scene->GetComponentDataArray<SphereCollider>());
	std::vector<BoxCollider>* dataBox = reinterpret_cast<std::vector<BoxCollider>*>(scene->GetComponentDataArray<BoxCollider>());



}

void ColliderSystem::Update(Scene* scene)
{
}

void ColliderSystem::LateUpdate(Scene* scene)
{
}

void ColliderSystem::Render(Shader& shader, Scene* scene)
{
	



}

void ColliderSystem::OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data)
{
}

bool ColliderSystem::CheckCollision(const SphereCollider& sphere1, const SphereCollider& sphere2)
{
	const Transform& s1 = *currentScene->GetComponent<Transform>(sphere1.entity);
	const Transform& s2 = *currentScene->GetComponent<Transform>(sphere2.entity);

	const Vector3 worldPosS1 = static_cast<const Vector3>(s1.World[3]);
	const Vector3 worldPosS2 = static_cast<const Vector3>(s2.World[3]);

	const float distance = Vector3::Distance(worldPosS1, worldPosS2);
	const float r1r2 = sphere1.radius + sphere2.radius;


	if (distance < r1r2)
	{

		return true;
	}

	return false;
}
