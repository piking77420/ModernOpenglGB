#pragma once
#include "LowRenderer/Light/Light.hpp"
#include "Core/ECS/ECSComponent.h"
#include "Physics/Transform/Transform.hpp"

class DirectionalLight : public EcsComponent<DirectionalLight> 
{
public:
	Light lightData;
	void ImguiWindowComponent() override;


	DirectionalLight();
	~DirectionalLight();

private:

};

