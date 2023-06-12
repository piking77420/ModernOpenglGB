#pragma once
#include "Collider/PlaneCollider.h"

class KillZone : public Component 
{
public:


	PlaneCollider* Planecollider;


	void Update(Scene* scene) override;

	KillZone(Entity& entity);
	~KillZone();

};

