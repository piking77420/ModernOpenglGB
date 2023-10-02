#pragma once
#include <glad/glad.h>
#include "Ressources/IResources/IResource.h"

class Shader;

class FrameBuffer
{
public:
	uint32_t FBO = 0 ;
	uint32_t framebufferTexture = 0 ;
	uint32_t RBO = 0 ;

	uint32_t rectVAO = 0 ;
	uint32_t rectVBO = 0 ;

	uint32_t widht = 0 ;
	uint32_t height = 0 ;

	virtual void Bind();
	virtual void UnBind();

	unsigned int GetTexture() const;
	void ResizeFrammeBuffer(float _width, float _height);
	virtual void InitResources();

	void DestroyBuffers();


	void InitVAOVBO();
	void DrawBuffer(const Shader& shader);
	FrameBuffer(int windowWidth, int windowHeight);
	~FrameBuffer();
	FrameBuffer();

};

