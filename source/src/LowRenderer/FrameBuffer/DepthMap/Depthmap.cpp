#include "LowRenderer/FrameBuffer/DepthMap/Depthmap.h"

Depthmap::Depthmap(uint32_t _widht, uint32_t _height) 

{
	widht = _widht;
	height = _height;
	Init();
}

void Depthmap::Init()
{
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, widht, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // attach depth texture as FBO's depth buffer
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Depthmap::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
}

void Depthmap::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Depthmap::Depthmap()
{
	widht = 4096;
    height = 4096;

	Init();
}


Depthmap::~Depthmap()
{
    if(glIsBuffer(depthMapFBO))
    {
        glDeleteBuffers(1, &depthMapFBO);

    }
    if (glIsTexture(depthMapFBO))
    {
        glDeleteTextures(1, &depthMap);
    }
}
