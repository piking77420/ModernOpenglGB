#pragma once
#include<LowRenderer/Material/Material.h>
#include "Core/ECS/ECSComponent.h"


class Model;
class Texture;
class Shader;

class MeshRenderer : public EcsComponent<MeshRenderer>
{
public:

	Material material;
	const Model* model;
	const Texture* diffuse;
	const Texture* specular;
	const Shader* shader;
private:
};

