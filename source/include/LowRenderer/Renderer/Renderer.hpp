#pragma once
#include "LowRenderer/FrameBuffer/FrameBuffer.h"
#include "LowRenderer/Light/DirectionalLight/DirectionalLight.hpp"
#include "LowRenderer/Light/SpothLight/SpothLight.hpp"
#include "LowRenderer/Light/PointLight/PointLight.hpp"


class Scene;
class Shader;
class MeshRenderer;
class FrammeBuffer;

enum MATERIALSHADER
{
	PHONG,
	PBR,
	MATERIALSHADERSIZE
};


class Renderer
{
public:

	static inline FrameBuffer* BindedFrameBuffer = nullptr;
	// Use If you want to draw the scene in a with a specific shader
	static void RendereScene(Scene* scene, Shader* shader);

	// Render Scene as usual
	static void RendereScene(Scene* scene);

	static void ResetViewPort();

	Renderer() = delete;
	~Renderer() = delete;

	static inline MATERIALSHADER shaderType = MATERIALSHADER::PHONG;

private:

	// mESH// 

	static void RenderMeshRender(const MeshRenderer* meshRender, Shader& shader, Scene* scene);
	static void RenderStencil(const MeshRenderer* meshRender,const Shader& shader, Scene* scene);

	static void RenderPhong(const MeshRenderer* meshRender, Shader& shader, Scene* scene);
	static void RenderPBR(const MeshRenderer* meshRender, Shader& shader, Scene* scene);

	// LIGHT // 

	static void ComputeLight(Shader& shader, Scene* scene);
	static void UpdateDirectionnalLights(std::vector<DirectionalLight>* data, Scene* scene);
	static void UpdatePointLights(std::vector<PointLight>* data, Scene* scene);
	static void UpdateSpothLights(std::vector<SpothLight>* data, Scene* scene);

	static void RenderDirectionalLight(const DirectionalLight* dirLight, Scene* scene);

	static inline Shader* m_CurrentShader = nullptr;
};

