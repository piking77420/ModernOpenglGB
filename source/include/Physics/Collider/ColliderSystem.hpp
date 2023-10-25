#pragma once
#include "Core/ECS/IECSSystem.h"
#include "Physics/Transform/Transform.hpp"
#include <array>

struct Collider;
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
	Scene* m_currentScene = nullptr;

	
	void CheckCollisionSphereSphere(SphereCollider& sphere1, SphereCollider& sphere2);

	void CheckCollisionBoxBox(BoxCollider& Box1, BoxCollider& Box2);

	void CheckCollisionBoxSphere(BoxCollider& sphere1, SphereCollider& sphere2);



	void ProcessSphereSphere(std::vector<SphereCollider>* sphereData);
	void ProcessBoxBox(std::vector<BoxCollider>* boxData);

	void ProcessSphereBox(std::vector<SphereCollider>* sphereData , std::vector<BoxCollider>* boxData);
	


	Vector3 DeterminateVectorNormal(const Vector3& normal, const Vector3& origin);

	// Sat box box Method
	Vector3 GetVertexBox(Transform& transform, const Vector3& halfLength, int vertexIndex);
	std::array<Vector3, 3> GetAxis(const std::array<Vector3, 8>& arrayOfVertices, const Transform& transfrom);
	void ProjectVerticesOnAxis(const std::array<Vector3, 8>& verticiesArray, const Vector3& axis, float& outmin, float& outmax);

};

