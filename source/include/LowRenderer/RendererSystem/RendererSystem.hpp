#pragma once
#include "Core/ECS/IECSSystem.h"
#include<string>
#include "Ressources/Shader/Shader.h"
class Scene;
class MeshRenderer;
class Model;

class RendererSystem : public IEcsSystem
{
public:

	std::string shaderName;

	void Init(Scene* scene) override;
	void Render(Scene* scene) override;
	RendererSystem(){};

	 ~RendererSystem() override {};

private:
	const Shader* shaderProgramm = nullptr;
	void RenderMeshRender(const MeshRenderer* meshRender , Scene* scene);
};

