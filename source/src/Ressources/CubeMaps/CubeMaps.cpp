#include "Ressources/CubeMaps/CubeMaps.h"
#include "External/Std_Image/std_image.h"
#include <vector>
namespace fs = std::filesystem;



void CubeMaps::BindCubeMap() const
{
    std::cout << ID << std::endl;
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void CubeMaps::UnBindCubeMap() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMaps::InitResource()
{

}




void CubeMaps::operator=(const CubeMaps& cubeMaps)
{
    this->height = cubeMaps.height;
    this->width = cubeMaps.width;
    this->ID = cubeMaps.ID;
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
    if(glIsTexture(ID))
    {
        glDeleteTextures(1, &ID);
    }
}

void CubeMaps::Load(std::vector<std::string>& allMapsFile)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
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

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}


