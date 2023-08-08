#pragma once
#include <vector>
#include "Physics/Transform/Transform.hpp"
#include "ToolBoxMathHeaders.h"

struct CollisionPoint
{
	float depht;
	Vector3 Normal;
};


struct Collider
{
	bool IsDrawing = true;
	std::vector<CollisionPoint> CollisionPoint;

};

