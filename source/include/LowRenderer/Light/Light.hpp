#pragma once
#include "Core/Math/ToolBoxMathHeaders.h"
#include "LowRenderer/FrameBuffer/DepthMap/Depthmap.h"

class Shader;
class Depthmap;


struct Light 
{
	Vector4 ambiantColor = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
	Vector4 diffuseColor = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
	Vector4 specularColor = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
	float SpecularStrengt = 32.f;
	Matrix4X4 LightSpaceMatrix;
	Depthmap depthmap;
};

