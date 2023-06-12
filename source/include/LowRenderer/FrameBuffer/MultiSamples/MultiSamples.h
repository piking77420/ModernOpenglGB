#pragma once
#include "LowRenderer/FrameBuffer/FrameBuffer.h"

class MultiSamples : public FrameBuffer
{

public:

	void BlitBuffers(unsigned int Framebuffer);
	MultiSamples(int samples);
	~MultiSamples();
};

