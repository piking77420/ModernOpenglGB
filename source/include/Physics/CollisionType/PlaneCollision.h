#pragma once
#include "Physics/CollisionType/CollisionType.h"


class Collider;

class PlaneCollision : public CollisionType
{
public:
	bool IsInfinite;

	bool IsInside(const Vector3& point);
	bool IsInside(Vector3 point , float radius);

	Vector3 GetNormalOffPlane() const;
	float GetDistanceFromPlane(const Vector3& point) const;
	void ImguiWindow() override;
	void Update(const Collider& collider) override;


	PlaneCollision();
	PlaneCollision(Entity& _currentTransform, const Vector3& _P1, const Vector3& _P2, bool _IsInfinit);
	// Neutral Point of the Plane P1(1,0,0) P2(0,0,1)
	PlaneCollision(Entity& _currentTransform, bool _IsInfinit);
	PlaneCollision(Entity& _currentTransform);

	~PlaneCollision();


	Vector3 m_P0;
	Vector3 m_P1;
	Vector3 m_P2;
protected:
	float GetD(const Vector3& point) const ;
	
};

