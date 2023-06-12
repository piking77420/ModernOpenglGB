#include "Scripts/KillZone.h"

KillZone::~KillZone()
{
}

KillZone::KillZone(Entity& entity) : Component(entity) , Planecollider(entity.GetComponent<PlaneCollider>())
{
}
void KillZone::Update(Scene* scene)
{
	if (!Planecollider)
		return;


	for (size_t i = 0; i < Planecollider->entitesHasBeenCollid.size(); i++)
	{
		if(Planecollider->entitesHasBeenCollid[i]->Tag == "Player")
		{
			Planecollider->entitesHasBeenCollid[i]->transform.pos = Vector3::Zero;
		}
	}
}