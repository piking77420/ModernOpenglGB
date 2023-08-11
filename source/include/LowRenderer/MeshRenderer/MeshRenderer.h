#pragma once
#include<LowRenderer/Material/Material.h>
#include "Core/ECS/ECSComponent.h"

class Mesh;
class Texture;
class Shader;

class MeshRenderer : public EcsComponent<MeshRenderer>
{
public:

	Material material;
	const Mesh* model;
	const Texture* diffuse = nullptr;
	const Texture* specular = nullptr;
	bool m_Stencil = false;

	void ImguiWindowComponent() override;

private:
};

