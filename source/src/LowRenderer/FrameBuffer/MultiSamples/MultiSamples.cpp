#include "LowRenderer/FrameBuffer/MultiSamples/MultiSamples.h"
#include "App/App.h"

MultiSamples::~MultiSamples()
{
}

void MultiSamples::BlitBuffers(unsigned int Framebuffer)
{

    glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, Framebuffer);
    glBlitFramebuffer(0, 0, windowWidth, windowHeight, 0, 0, windowWidth, windowHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

MultiSamples::MultiSamples(int samples)
{
    // Create Frame Buffer Object

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);


    // Create Framebuffer Texture

    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, windowWidth, windowHeight,GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture, 0);


    // Create Render Buffer Object

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER,samples ,GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    auto FrameBufferError = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (FrameBufferError != GL_FRAMEBUFFER_COMPLETE)
    {
        Debug::Log->LogWarning(" FRAMME BUFFER ERROR " + std::to_string(FrameBufferError));
    }


}
