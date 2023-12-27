#pragma once
#include "Core/Math/ToolBoxMathHeaders.h"

class Shader;
class Depthmap;


struct Light 
{
	Vector4 color  = Vector4(1.F, 1.F, 1.F, 1.F);
	Matrix4X4 LightSpaceMatrix;
	float minimumRange = 2.5f;
	float maxRange = 100.f;
	float size = 10.f;
};

