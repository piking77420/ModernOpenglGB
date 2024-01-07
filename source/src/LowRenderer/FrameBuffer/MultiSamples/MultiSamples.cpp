#include "LowRenderer/FrameBuffer/MultiSamples/MultiSamples.h"
#include "App/App.h"

MultiSamples::~MultiSamples()
{
    DestroyBuffers();
}

void MultiSamples::DestroyBuffers()
{
    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1, &framebufferTexture);
    glDeleteRenderbuffers(1, &RBO);

    glDeleteFramebuffers(1, &intermediateFBO);
    glDeleteTextures(1, &screenTexture);
}

void MultiSamples::Init()
{

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    // create a multisampled color attachment texture
    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, Samples, GL_RGB16F, widht, height, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture, 0);


    // create a (also multisampled) renderbuffer object for depth and stencil attachments
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, Samples, GL_DEPTH24_STENCIL8, widht, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // configure second post-processing framebuffer
    glGenFramebuffers(1, &intermediateFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBO);

    // create a color attachment texture
    glGenTextures(1, &screenTexture);
    glBindTexture(GL_TEXTURE_2D, screenTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widht, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);

}

void MultiSamples::BlitBuffers()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFBO);
    glBlitFramebuffer(0, 0, widht, height, 0, 0, widht, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void MultiSamples::ResizeFrammeBuffer(float _width, float _height)
{
    widht = _width;
    height = _height;
    Init();

}

void MultiSamples::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

}

void MultiSamples::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}



MultiSamples::MultiSamples(int samples) : Samples(samples)
{
    Init();
}

MultiSamples::MultiSamples()
{
    glGetIntegerv(GL_MAX_SAMPLES, &Samples);

}
