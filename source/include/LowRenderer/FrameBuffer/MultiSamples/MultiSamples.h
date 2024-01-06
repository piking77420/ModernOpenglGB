#pragma once
#include "LowRenderer/FrameBuffer/FrameBuffer.h"

class MultiSamples : public FrameBuffer
{

public:

	void BlitBuffers();
	virtual void ResizeFrammeBuffer(float _width, float _height) override;

	virtual void Bind();
	virtual void UnBind();


	MultiSamples(int samples);
	MultiSamples();

	~MultiSamples();

	GLuint screenTexture;
	GLuint intermediateFBO;

protected:

	virtual void DestroyBuffers() override;
	virtual void Init() override;

	int Samples =  4;
};

