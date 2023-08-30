#pragma once
#include<LowRenderer/Material/Material.h>
#include "Core/ECS/ECSComponent.h"
#include "Ressources/Mesh/Mesh.h"

class Texture;
class Shader;

class MeshRenderer : public EcsComponent<MeshRenderer>
{
public:

	Material material;
	Mesh mesh;
	bool stencil = false;

	void ImguiWindowComponent() override;

private:
};

