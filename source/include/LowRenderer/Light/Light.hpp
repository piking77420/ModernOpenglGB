#pragma once
#include "Core/Math/ToolBoxMathHeaders.h"

class Shader;
class Depthmap;


struct Light 
{
	Vector4 color  = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
	Matrix4X4 LightSpaceMatrix;
	float minimumRange = 2.5f;
	float maxRange = 100.f;
	float size = 10.f;
};

