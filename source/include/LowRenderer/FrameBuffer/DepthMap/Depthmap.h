#pragma once
#include "LowRenderer/FrameBuffer/FrameBuffer.h"

class Depthmap : public FrameBuffer
{
public:


	Depthmap(uint32_t _widht,uint32_t _height);

	 void Init() override;

	Depthmap();
	~Depthmap();
};

