#pragma once
#include "LowRenderer/Light/Light.hpp"
#include "Core/ECS/ECSComponent.h"
#include "Physics/Transform/Transform.hpp"
#include "LowRenderer/FrameBuffer/DepthMap/Depthmap.h"

class DirectionalLight : public EcsComponent<DirectionalLight> 
{
public:
	Light lightData;
	Depthmap depthmap;

	float c1 = 0.2f;
	float c2 = 0.2f;
	float c3 = 0.2f;

	void ImguiWindowComponent() override;


	DirectionalLight();
	~DirectionalLight();

private:

};

