#pragma once
#include <glad/glad.h>
#include "Ressources/IResources/IResource.h"

class Shader;

class FrameBuffer
{
public:
	unsigned int FBO ;
	unsigned int framebufferTexture;
	unsigned int RBO;

	unsigned int rectVAO;
	unsigned int rectVBO;


	int widht;
	int height;
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

