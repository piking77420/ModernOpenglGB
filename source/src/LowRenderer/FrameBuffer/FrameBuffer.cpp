#include "LowRenderer/FrameBuffer/FrameBuffer.h"
#include <Debug/Debug.h>
#include "Ressources/Shader/Shader.h"


void FrameBuffer::InitResources()
{
    // Create Frame Buffer Object



    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);


    // Create Framebuffer Texture

    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widht, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);


    // Create Render Buffer Object

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, widht, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    auto FrameBufferError = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (FrameBufferError != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG(" FRAMME BUFFER ERROR " + std::to_string(FrameBufferError),STATELOG::CRITICALERROR);
    }

    InitVAOVBO();
}


void FrameBuffer::InitVAOVBO()
{

	float rectangleVertices[] = {
		// Coords    // texCoords
			1.0f, -1.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f, 0.0f,
			-1.0f, 1.0f, 0.0f, 1.0f,

			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f, 1.0f
	};


    // Prepare framebuffer rectangle VBO and VAO
    glGenVertexArrays(1, &rectVAO);
    glGenBuffers(1, &rectVBO);
    glBindVertexArray(rectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));


}

void FrameBuffer::DrawBuffer(const Shader& shader)
{
    shader.Use();
    glBindVertexArray(rectVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}


void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void FrameBuffer::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int FrameBuffer::GetTexture() const
{
    return framebufferTexture;
}

void FrameBuffer::ResizeFrammeBuffer(float _width, float _height)
{
    widht = _width;
    height = _height;
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
}

FrameBuffer::FrameBuffer(int windowWidth,int windowHeight)
{
    widht = windowWidth;
    height = windowHeight;
}

void FrameBuffer::DestroyBuffers()
{
    if (glIsBuffer(FBO))
        glDeleteBuffers(1, &FBO);

    if (glIsBuffer(rectVAO))
        glDeleteBuffers(1, &rectVAO);

    if (glIsBuffer(rectVBO))
        glDeleteBuffers(1, &rectVBO);

    if (glIsTexture(framebufferTexture))
        glDeleteTextures(1, &framebufferTexture);

    if (glIsRenderbuffer(RBO))
        glDeleteRenderbuffers(1, &RBO);
}


FrameBuffer::FrameBuffer()
{
    InitVAOVBO();
}

FrameBuffer::~FrameBuffer()
{
    DestroyBuffers();
}
