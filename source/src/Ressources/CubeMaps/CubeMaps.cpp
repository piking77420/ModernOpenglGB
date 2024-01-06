#include "Ressources/CubeMaps/CubeMaps.h"
#include "External/Std_Image/std_image.h"
#include <vector>
namespace fs = std::filesystem;



void CubeMaps::BindCubeMap() const
{
    glBindTexture(type, ID);
}

void CubeMaps::UnBindCubeMap() const
{
    glBindTexture(type, 0);
}

void CubeMaps::InitResource()
{
  if(flags == TextureFlags::HDR)
  {
      InitFrammeBuffer();
  }
  else
  {
     // InitBox();
  }


}


void CubeMaps::operator=(const CubeMaps& cubeMaps)
{
    this->slot = cubeMaps.slot;
    this->height = cubeMaps.height;
    this->width = cubeMaps.width;
    this->ID = cubeMaps.ID;
    this->type = cubeMaps.type;
}


CubeMaps::CubeMaps(std::vector<std::string>& allMapsFile, TextureFlags flags)
{
    type = GL_TEXTURE_CUBE_MAP;

    if(flags == HDR)
    {
        LoadHDR(allMapsFile);
    }
    else
    {
        Load(allMapsFile);
    }
 

}

CubeMaps::CubeMaps(const std::string& hdrMap)
{
    flags = TextureFlags::HDR;

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
    float* data = stbi_loadf(hdrMap.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load HDR image." << std::endl;
    }




}


CubeMaps::~CubeMaps()
{
    if (glIsBuffer(VAO))
    {
        glDeleteBuffers(1, &VAO);
    }

    if (glIsBuffer(VBO))
    {
        glDeleteBuffers(1, &VBO);
    }
    if(glIsTexture(ID))
    {
        glDeleteTextures(1, &ID);
    }
}

void CubeMaps::Load(std::vector<std::string>& allMapsFile)
{
    glGenTextures(1, &ID);
    glBindTexture(type, ID);
    unsigned char* data;

    flags = TextureFlags::HDR;

    for (unsigned int i = 0; i < allMapsFile.size(); i++)
    {
        stbi_set_flip_vertically_on_load(false);

        data = stbi_load(allMapsFile[i].c_str(), &width, &height, &nbrOfChannel, 0);
        GLuint format = Texture::GetFormat(nbrOfChannel);

        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data
        );

        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            LOG("Cubemap tex failed to load at path: " + allMapsFile[i], STATELOG::WARNING);
            stbi_image_free(data);
        }

    }

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}


void CubeMaps::LoadHDR(std::vector<std::string>& allMapsFile)
{
    glGenTextures(1, &ID);
    glBindTexture(type, ID);
    float* data;


    for (unsigned int i = 0; i < allMapsFile.size(); i++)
    {
        stbi_set_flip_vertically_on_load(false);

        data = stbi_loadf(allMapsFile[i].c_str(), &width, &height, &nbrOfChannel, 0);
        GLuint format = Texture::GetFormat(nbrOfChannel);

        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, GL_FLOAT, width, height, 0, GL_RGB, GL_FLOAT, data
        );

        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_FLOAT, width, height, 0, GL_RGB, GL_FLOAT, data
            );
            stbi_image_free(data);
        }
        else
        {
            LOG("Cubemap tex failed to load at path: " + allMapsFile[i], STATELOG::WARNING);
            stbi_image_free(data);
        }

    }

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CubeMaps::InitFrammeBuffer()
{
    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        // note that we store each face with 16 bit floating point values
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F,
            512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}
