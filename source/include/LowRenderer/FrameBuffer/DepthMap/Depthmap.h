#pragma once
#include "LowRenderer/FrameBuffer/FrameBuffer.h"

class Depthmap 
{
public:
	unsigned int  depthMapFBO;
	unsigned int depthMap;
	uint32_t widht;
	uint32_t height;

	Depthmap(uint32_t _widht,uint32_t _height);

	 void InitResources();
	 void Bind();
	 void UnBind();

	Depthmap();
	~Depthmap();
};

