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
	const Texture* diffuse = nullptr;
	const Texture* specular = nullptr;
	const Shader* shader = nullptr;
	bool m_Stencil = false;

	void ImguiWindowComponent() override;

private:
};

