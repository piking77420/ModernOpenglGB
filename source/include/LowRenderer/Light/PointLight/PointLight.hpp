#pragma once
#include "LowRenderer/Light/Light.hpp"
#include "Core/ECS/ECSComponent.h"




class PointLight : public EcsComponent<PointLight>
{
public:
	
	Light lightData;

	PointLight();
	~PointLight();

private:

};

