#pragma once
#include "Mathf.h"
#include "CollisionType.h"
#include <vector>

class AABCollision : public CollisionType
{
public:
	void ImguiWindow() override;
	
	void Update(const Collider& collider) override;

	bool IsInside(Vector3 point, float radius)	;

	std::vector<Vector3> mverticies;
	Vector3 GetNormal()const ;
	Vector3 posMin;
	Vector3 posMax;

	Vector3& Size;
	AABCollision(Entity& entity, std::vector<Vector3> verticies, Vector3& size);
	~AABCollision();

private:
	Vector3 LocalposMin;
	Vector3 LocalposMax;
	Vector3 Midpos;
	float GetD(const Vector3& point) const;

};


