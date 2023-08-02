#pragma once
#include "LowRenderer/Light/Light.hpp"
#include "Core/ECS/ECSComponent.h"


class DirectionalLight : public EcsComponent<DirectionalLight> 
{
public:
	Light lightData;
	Vector3 direction = Vector3::Zero();

	DirectionalLight();
	~DirectionalLight();

private:

};

