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

	ImplementIEcsSystem;

	RendererSystem(){};

	 ~RendererSystem(){};

private:
	const Shader* shaderProgramm = nullptr;
	void RenderMeshRender(const MeshRenderer* meshRender , Scene* scene);
};

