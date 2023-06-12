#pragma once
#include "Physics/CollisionType/CollisionType.h"

enum Axes 
{
	UP,
	RIGHT,
	FORWARD
};

struct Faces
{
	Vector3 P0;
	Vector3 P1;
	Vector3 P2;

	Vector3 WP0;
	Vector3 WP1;
	Vector3 WP2;

	Vector3 Normal;
	Axes Axe;
	Faces(const Vector3& _P0, const Vector3& _P1 , const Vector3& _P2s, const Axes _Axe);
};

class BoxCollisionType : public CollisionType
{
public:
	

	std::vector<Faces> m_BoxFaces;
	void Update(const Collider& collider) override;
	Vector3 GetNormal(const Faces& faces);
	BoxCollisionType(Entity& entity);
	~BoxCollisionType();
private:
	void SetFaces();
};

