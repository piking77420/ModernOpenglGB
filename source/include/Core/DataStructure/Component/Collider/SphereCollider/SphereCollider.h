#pragma once
#include "Collider/Collider.h"


class SphereCollider : public Collider
{
public:

		
	float radius;

	void Collision(SphereCollider* sphereCollider) override;
	void ImguiWindowComponents() override;

	SphereCollider();
	SphereCollider(float radius);
	~SphereCollider();
private:
	bool m_ShowGizmo = false;
};

