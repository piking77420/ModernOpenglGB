#include "LowRenderer/Renderer/Renderer.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Ressources/Scene/Scene.h"

FrameBuffer* Renderer::OpenGlRenderToImgui = new FrameBuffer(800, 800);


void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	if (!OpenGlRenderToImgui)
		return;
	glViewport(0, 0, width, height);
	OpenGlRenderToImgui->ResizeFrammeBuffer(width, height);
}

void Renderer::PreRendererScene(Scene* scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	OpenGlRenderToImgui->Bind();

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

}

void Renderer::RendereScene(Scene* scene)
{
	scene->Render();
	OpenGlRenderToImgui->UnBind();
}

Renderer::Renderer()
{
	OpenGlRenderToImgui->Init();
}

Renderer::~Renderer()
{
	delete OpenGlRenderToImgui;
}
