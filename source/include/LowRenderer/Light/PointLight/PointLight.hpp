#pragma once
#include "LowRenderer/Light/Light.hpp"
#include "Core/ECS/ECSComponent.h"
#include "Ressources/CubeMaps/DepthCubeMap.h"
#include<array>


class PointLight : public EcsComponent<PointLight>
{
public:
	
	Light lightData;
	Matrix4X4 ShadowProj;
	std::array<Matrix4X4, 6> shadowTransforms;
	DepthCubeMap depthMap;
	void ImguiWindowComponent() override;


	PointLight();
	~PointLight();

private:

	
};

