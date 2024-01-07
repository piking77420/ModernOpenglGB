#pragma once
#include "CubeMaps.h"




class DepthCubeMap : public CubeMaps
{
public:

	DepthCubeMap();
	~DepthCubeMap();

	void BindDethFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	}

	void UnBindDethFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	int ShadowMapWidth = 0;
	int ShadowMapHeight = 0;

private:
	GLuint depthMapFBO = 0;
	

};