#pragma once
#include "Collider/Collider.h"


class SphereCollider : public Collider
{
public:

		
	float radius;
	
	SphereCollider(Entity& entity);
	SphereCollider(Entity& entity,float radius);
	~SphereCollider();
	void ImguiWindowComponents() override;



	

private:
	bool m_ShowGizmo = false;
};
