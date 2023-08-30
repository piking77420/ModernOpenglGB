#pragma once
#include "LowRenderer/Light/Light.hpp"
#include "Core/ECS/ECSComponent.h"
#include "Ressources/CubeMaps/CubeMaps.h"
#include<array>


class PointLight : public EcsComponent<PointLight>
{
public:
	
	Light lightData;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;
	CubeMaps depthMap;
	GLuint depthMapFBO;

	std::array<Matrix4X4, 6> shadowTransforms;
	PointLight();
	~PointLight();

private:

	
};

