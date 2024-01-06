#pragma once
#include "LowRenderer/FrameBuffer/FrameBuffer.h"

class Scene;
class Shader;
class MeshRenderer;
class FrammeBuffer;



class Renderer
{
public:

	static inline FrameBuffer* BindedFrameBuffer = nullptr;
	// Use If you want to draw the scene in a with a specific shader
	static void RendereScene(Scene* scene, Shader* shader);

	// Render Scene as usual
	static void RendereScene(Scene* scene);

	Renderer() = delete;
	~Renderer() = delete;
private:
	static void RenderMeshRender(const MeshRenderer* meshRender, Shader& shader, Scene* scene);
	static void RenderStencil(const MeshRenderer* meshRender,const Shader& shader, Scene* scene);

	static void RenderPhong(const MeshRenderer* meshRender, Shader& shader, Scene* scene);
	static void RenderPBR(const MeshRenderer* meshRender, Shader& shader, Scene* scene);



};

