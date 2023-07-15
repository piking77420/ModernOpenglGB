#include "Ressources/SkyBox/SkyBox.h"


float SkyBox::CUBEMAPSIZE = 1000.f;

void SkyBox::Draw() const 
{

    // TO DO RESERVE FOR EACH TEXTRURE A SLOT 
    m_Cubemaps.BindCubeMap();
    glDepthFunc(GL_LEQUAL);
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0 + m_Cubemaps.slot);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
    m_Cubemaps.UnBindCubeMap();

}

void SkyBox::operator=(const SkyBox& skybox)
{

    m_Cubemaps = skybox.m_Cubemaps;
}

SkyBox::SkyBox(CubeMaps& cubemaps) : m_Cubemaps(cubemaps)
{
    InitBufferCubaMaps();
}


SkyBox::SkyBox()
{
    InitBufferCubaMaps();
}

SkyBox::~SkyBox() 
{
}

void SkyBox::InitBufferCubaMaps()
{
    float skyboxVertices[] = {
        // positions          
        -CUBEMAPSIZE,  CUBEMAPSIZE, -CUBEMAPSIZE,
        -CUBEMAPSIZE, -CUBEMAPSIZE, -CUBEMAPSIZE,
         CUBEMAPSIZE, -CUBEMAPSIZE, -CUBEMAPSIZE,
         CUBEMAPSIZE, -CUBEMAPSIZE, -CUBEMAPSIZE,
         CUBEMAPSIZE,  CUBEMAPSIZE, -CUBEMAPSIZE,
        -CUBEMAPSIZE,  CUBEMAPSIZE, -CUBEMAPSIZE,

        -CUBEMAPSIZE, -CUBEMAPSIZE,  CUBEMAPSIZE,
        -CUBEMAPSIZE, -CUBEMAPSIZE, -CUBEMAPSIZE,
        -CUBEMAPSIZE,  CUBEMAPSIZE, -CUBEMAPSIZE,
        -CUBEMAPSIZE,  CUBEMAPSIZE, -CUBEMAPSIZE,
        -CUBEMAPSIZE,  CUBEMAPSIZE,  CUBEMAPSIZE,
        -CUBEMAPSIZE, -CUBEMAPSIZE,  CUBEMAPSIZE,

         CUBEMAPSIZE, -CUBEMAPSIZE, -CUBEMAPSIZE,
         CUBEMAPSIZE, -CUBEMAPSIZE,  CUBEMAPSIZE,
         CUBEMAPSIZE,  CUBEMAPSIZE,  CUBEMAPSIZE,
         CUBEMAPSIZE,  CUBEMAPSIZE,  CUBEMAPSIZE,
         CUBEMAPSIZE,  CUBEMAPSIZE, -CUBEMAPSIZE,
         CUBEMAPSIZE, -CUBEMAPSIZE, -CUBEMAPSIZE,

        -CUBEMAPSIZE, -CUBEMAPSIZE,  CUBEMAPSIZE,
        -CUBEMAPSIZE,  CUBEMAPSIZE,  CUBEMAPSIZE,
         CUBEMAPSIZE,  CUBEMAPSIZE,  CUBEMAPSIZE,
         CUBEMAPSIZE,  CUBEMAPSIZE,  CUBEMAPSIZE,
         CUBEMAPSIZE, -CUBEMAPSIZE,  CUBEMAPSIZE,
        -CUBEMAPSIZE, -CUBEMAPSIZE,  CUBEMAPSIZE,

        -CUBEMAPSIZE,  CUBEMAPSIZE, -CUBEMAPSIZE,
         CUBEMAPSIZE,  CUBEMAPSIZE, -CUBEMAPSIZE,
         CUBEMAPSIZE,  CUBEMAPSIZE,  CUBEMAPSIZE,
         CUBEMAPSIZE,  CUBEMAPSIZE,  CUBEMAPSIZE,
        -CUBEMAPSIZE,  CUBEMAPSIZE,  CUBEMAPSIZE,
        -CUBEMAPSIZE,  CUBEMAPSIZE, -CUBEMAPSIZE,

        -CUBEMAPSIZE, -CUBEMAPSIZE, -CUBEMAPSIZE,
        -CUBEMAPSIZE, -CUBEMAPSIZE,  CUBEMAPSIZE,
         CUBEMAPSIZE, -CUBEMAPSIZE, -CUBEMAPSIZE,
         CUBEMAPSIZE, -CUBEMAPSIZE, -CUBEMAPSIZE,
        -CUBEMAPSIZE, -CUBEMAPSIZE,  CUBEMAPSIZE,
         CUBEMAPSIZE, -CUBEMAPSIZE,  CUBEMAPSIZE
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

}
