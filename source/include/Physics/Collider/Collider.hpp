#pragma once
#include <vector>
#include "Physics/Transform/Transform.hpp"
#include "ToolBoxMathHeaders.h"
#include "Core/ECS/Entity.h"

enum class CollisionType
{
	Sphere,Box
};


struct PhyscicalMaterial
{
	float friction = 0.6f;
	float Boundciness = 0.0f;

};

struct CollisionPoint
{
	float depht = 0 ;
	Vector3 collisionPoint;
	Vector3 Normal = Vector3::Zero();
	uint32_t entityIDBeenCollidWith;
	CollisionPoint(uint32_t _entityIDBeenCollidWith, float _depth, Vector3 _normal) :entityIDBeenCollidWith(_entityIDBeenCollidWith) ,depht(_depth), Normal(_normal) {};
	CollisionPoint(): entityIDBeenCollidWith(EntityNULL) {};
};


struct Collider
{
	CollisionType collisionType;
	bool IsDrawing = true;
	bool IsTrigger = false;
	std::vector<CollisionPoint> CollisionPoint;
	PhyscicalMaterial physcicalMaterial;
};

