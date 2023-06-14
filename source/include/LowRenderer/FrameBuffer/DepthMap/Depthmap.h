#pragma once
#include "LowRenderer/FrameBuffer/FrameBuffer.h"

class Depthmap : public FrameBuffer
{
public:


	int widht;
	int height;
	Depthmap();
	~Depthmap();
};

