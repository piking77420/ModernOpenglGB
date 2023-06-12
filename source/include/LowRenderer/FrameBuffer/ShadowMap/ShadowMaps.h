#pragma once
#include "LowRenderer/FrameBuffer/FrameBuffer.h"
class ShadowMaps : public FrameBuffer 
{

public:

	int widht;
	int height;

	ShadowMaps(unsigned int  _widht, unsigned int _height);
	~ShadowMaps();

};

