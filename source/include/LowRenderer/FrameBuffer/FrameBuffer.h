#pragma once
#include <glad/glad.h>
#include "Ressources/IResources/IResource.h"

class Shader;

class FrameBuffer
{
public:
	uint32_t FBO;
	uint32_t framebufferTexture;
	uint32_t RBO;

	uint32_t rectVAO;
	uint32_t rectVBO;

	uint32_t widht;
	uint32_t height;

	virtual void Bind();
	virtual void UnBind();

	unsigned int GetTexture() const;
	void ResizeFrammeBuffer(float _width, float _height);
	virtual void Init();


	void InitVAOVBO();
	void DrawBuffer(const Shader& shader);
	FrameBuffer(int windowWidth, int windowHeight);
	~FrameBuffer();
	FrameBuffer();

};

