#pragma once
#include "LowRenderer/FrameBuffer/FrameBuffer.h"

class Scene;

class Renderer
{
public:

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);


	void PreRendererScene(Scene* scene);
	void RendereScene(Scene* scene);

	Renderer();
	~Renderer();
	static FrameBuffer* OpenGlRenderToImgui;
private:
};

