#pragma once
#include "Core/ECS/IECSSystem.h"
#include <ToolBoxMathHeaders.h>
class Rigidbody;
class Transfrom;

class PhysicsSystem : public IEcsSystem
{
	ImplementIEcsSystem;
	static float FixedDelatime;


	static inline Vector3 Gravity = Vector3(0,9.81f,0);
	PhysicsSystem(){};
	~PhysicsSystem(){};
private:

	void ApplieGravity(Scene* scene,std::vector<Rigidbody>* rigidBodys);


};

