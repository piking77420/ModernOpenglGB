#pragma once
#include "Core/ECS/IECSSystem.h"

class Collider;
class SphereCollider;
class BoxCollider;

class ColliderSystem : public IEcsSystem
{
public:
	void Init(Scene* scene) override; 
	void Awake(Scene* scene) override; 
	void Start(Scene* scene) override; 
	void FixedUpdate(Scene* scene) override; 
	void Update(Scene* scene) override; 
	void LateUpdate(Scene* scene) override; 
	void Render(Shader& shader, Scene* scene) override; 
	void OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data) override;

	ColliderSystem() {  };
	~ColliderSystem(){}
private:
	const Scene* currentScene;

	bool CheckCollision(const SphereCollider& sphere1, const SphereCollider& sphere2);

	bool CheckCollision(const BoxCollider& sphere1, const BoxCollider& sphere2);

	bool CheckCollision(const BoxCollider& sphere1, const SphereCollider& sphere2);



};

