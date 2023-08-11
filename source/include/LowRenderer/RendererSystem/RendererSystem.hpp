#pragma once
#include "Core/ECS/IECSSystem.h"
#include<string>
#include "Ressources/Shader/Shader.h"
class Scene;
class MeshRenderer;
class Mesh;

class RendererSystem : public IEcsSystem
{
public:


	ImplementIEcsSystem;


	RendererSystem(){};

	 ~RendererSystem(){};

private:
	void RenderMeshRender(const MeshRenderer* meshRender , Shader& shader, Scene* scene);
};

