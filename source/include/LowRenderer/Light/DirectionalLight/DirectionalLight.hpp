#pragma once
#include "LowRenderer/Light/Light.hpp"
#include "Core/ECS/ECSComponent.h"
#include "Physics/Transform/Transform.hpp"
#include "LowRenderer/FrameBuffer/DepthMap/Depthmap.h"

class DirectionalLight : public EcsComponent<DirectionalLight> 
{
public:
	Light lightData;
	uint32_t filterSize = 2.f;
	Depthmap depthmap;


	void ImguiWindowComponent() override;


	DirectionalLight();
	~DirectionalLight();

private:

};

