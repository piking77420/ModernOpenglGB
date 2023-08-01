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
	const Shader* shaderProgramm;

	void Init(Scene* scene) override;
	void Render(Scene* scene) override;
	RendererSystem(){};

	 ~RendererSystem() override {};

private:
	void RenderMeshRender(const MeshRenderer* meshRender , const Scene* scene);
};

