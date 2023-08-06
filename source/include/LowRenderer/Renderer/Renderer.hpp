#pragma once

class Scene;

class Renderer
{
public:



	void PreRendererScene(Scene* scene);
	void RendereScene(Scene* scene);

	Renderer();
	~Renderer();
private:
};

