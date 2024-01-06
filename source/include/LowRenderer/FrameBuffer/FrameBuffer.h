#pragma once
#include <glad/glad.h>
#include "Ressources/IResources/IResource.h"

class Shader;

class FrameBuffer
{
public:
	uint32_t FBO = 0 ;
	uint32_t RBO = 0 ;
	uint32_t framebufferTexture = 0 ;

	uint32_t widht = 800;
	uint32_t height = 800;

	virtual void Bind();
	virtual void UnBind();

	virtual void ResizeFrammeBuffer(float _width, float _height);
	static void DrawQuad();


	FrameBuffer(int windowWidth, int windowHeight);
	~FrameBuffer();
	FrameBuffer();
protected:
	virtual void DestroyBuffers();
	virtual void Init();

	static inline GLuint quadVAO;
	static inline GLuint quadVBO;
	
};

