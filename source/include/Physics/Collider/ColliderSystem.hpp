#pragma once
#include "Core/ECS/IECSSystem.h"
#include "Physics/Transform/Transform.hpp"
#include <array>


class Collider;
class SphereCollider;
class BoxCollider;

class ColliderSystem : public IEcsSystem
{
public:
	void Init(Scene* scene) override; 
	void Awake(Scene* scene) override; 
	void Start(Scene* scene) override; 
	void OnDrawGizmo(Scene* scene) override;
	void FixedUpdate(Scene* scene) override; 
	void Update(Scene* scene) override; 
	void LateUpdate(Scene* scene) override; 
	void Render(Shader& shader, Scene* scene) override; 
	void OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data) override;

	ColliderSystem() {  };
	~ColliderSystem(){}
private:
	Scene* currentScene;



	bool CheckCollision(SphereCollider& sphere1, SphereCollider& sphere2);

	bool CheckCollision(BoxCollider& Box1, BoxCollider& Box2);

	bool CheckCollision(BoxCollider& sphere1, SphereCollider& sphere2);

	Vector3 GetVertexBox(Transform& transform, const Vector3& halfLength, int vertexIndex);
	std::array<Vector3, 6> GetAxis(std::array<Vector3,8> arrayOfVerticies);


	void ProjectVerticesOnAxis(const std::array<Vector3, 8>& verticiesArray, const Vector3& axis, float& outmin, float& outmax);


};

