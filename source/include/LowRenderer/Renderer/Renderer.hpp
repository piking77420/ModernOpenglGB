#pragma once

class Scene;
class Shader;
class MeshRenderer;
class Renderer
{
public:



	void RendereScene(Scene* scene, Shader* shader);

	Renderer();
	~Renderer();
private:
	void RenderMeshRender(const MeshRenderer* meshRender, Shader& shader, Scene* scene);
};

