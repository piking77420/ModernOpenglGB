#pragma once
#include "LowRenderer/Light/Light.hpp"
#include "Core/ECS/ECSComponent.h"
#include "LowRenderer/FrameBuffer/DepthMap/Depthmap.h"


class SpothLight : public EcsComponent<SpothLight>
{
public:
	Light lightData;
	Vector3 direction = Vector3::Forward();

	float cutOff = 12.5f * Math::Deg2Rad;	
	float outerCutOff = 15.f * Math::Deg2Rad;
	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	Depthmap depthmap;

	SpothLight();
	~SpothLight();

private:

};

