#pragma once
#include "LowRenderer/Light/Light.hpp"
#include "Core/ECS/ECSComponent.h"


class SpothLight : public EcsComponent<SpothLight>
{
public:
	Light lightData;



	SpothLight();
	~SpothLight();

private:

};

