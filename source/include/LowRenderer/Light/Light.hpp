#pragma once
#include "Core/Math/ToolBoxMathHeaders.h"
#include "LowRenderer/FrameBuffer/DepthMap/Depthmap.h"

class Shader;
class Depthmap;


struct Light 
{
	Vector4 color  = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
	Matrix4X4 LightSpaceMatrix;
	Depthmap depthmap;
};

