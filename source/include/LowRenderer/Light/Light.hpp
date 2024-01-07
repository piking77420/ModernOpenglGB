#pragma once
#include "Core/Math/ToolBoxMathHeaders.h"

class Shader;
class Depthmap;


struct OffSetTexture
{

	OffSetTexture(int windowSize, int FilterSize);
	void BindTexture(uint32_t bindingLoc);

	uint32_t textureObj;
private:

	void CreateTextureOffSet(int windowSize, int FilterSize,const std::vector<float>& data);
};


struct Light 
{
	Vector4 color  = Vector4(1.F, 1.F, 1.F, 1.F);
	Matrix4X4 LightSpaceMatrix;
	float intensity = 1;
	float minimumRange = 2.5f;
	float maxRange = 100.f;
	float size = 10.f;
};

