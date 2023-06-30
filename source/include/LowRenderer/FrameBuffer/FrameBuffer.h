#pragma once
#include <glad/glad.h>
#include "Ressources/IResources/IResource.h"

class Shader;

class FrameBuffer : public IResource
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
	void ResizeFrammeBuffer(float width, float height);
	void Init() override;


	void InitVAOVBO();
	void DrawBuffer(const Shader& shader);
	FrameBuffer(int windowWidth, int windowHeight);
	~FrameBuffer();
	FrameBuffer();

};

