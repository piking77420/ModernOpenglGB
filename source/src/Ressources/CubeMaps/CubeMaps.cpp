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

void CubeMaps::Init()
{
    float skyboxVertices[] = {
        // positions          
        -cubeMapSize,  cubeMapSize, -cubeMapSize,
        -cubeMapSize, -cubeMapSize, -cubeMapSize,
         cubeMapSize, -cubeMapSize, -cubeMapSize,
         cubeMapSize, -cubeMapSize, -cubeMapSize,
         cubeMapSize,  cubeMapSize, -cubeMapSize,
        -cubeMapSize,  cubeMapSize, -cubeMapSize,

        -cubeMapSize, -cubeMapSize,  cubeMapSize,
        -cubeMapSize, -cubeMapSize, -cubeMapSize,
        -cubeMapSize,  cubeMapSize, -cubeMapSize,
        -cubeMapSize,  cubeMapSize, -cubeMapSize,
        -cubeMapSize,  cubeMapSize,  cubeMapSize,
        -cubeMapSize, -cubeMapSize,  cubeMapSize,

         cubeMapSize, -cubeMapSize, -cubeMapSize,
         cubeMapSize, -cubeMapSize,  cubeMapSize,
         cubeMapSize,  cubeMapSize,  cubeMapSize,
         cubeMapSize,  cubeMapSize,  cubeMapSize,
         cubeMapSize,  cubeMapSize, -cubeMapSize,
         cubeMapSize, -cubeMapSize, -cubeMapSize,

        -cubeMapSize, -cubeMapSize,  cubeMapSize,
        -cubeMapSize,  cubeMapSize,  cubeMapSize,
         cubeMapSize,  cubeMapSize,  cubeMapSize,
         cubeMapSize,  cubeMapSize,  cubeMapSize,
         cubeMapSize, -cubeMapSize,  cubeMapSize,
        -cubeMapSize, -cubeMapSize,  cubeMapSize,

        -cubeMapSize,  cubeMapSize, -cubeMapSize,
         cubeMapSize,  cubeMapSize, -cubeMapSize,
         cubeMapSize,  cubeMapSize,  cubeMapSize,
         cubeMapSize,  cubeMapSize,  cubeMapSize,
        -cubeMapSize,  cubeMapSize,  cubeMapSize,
        -cubeMapSize,  cubeMapSize, -cubeMapSize,

        -cubeMapSize, -cubeMapSize, -cubeMapSize,
        -cubeMapSize, -cubeMapSize,  cubeMapSize,
         cubeMapSize, -cubeMapSize, -cubeMapSize,
         cubeMapSize, -cubeMapSize, -cubeMapSize,
        -cubeMapSize, -cubeMapSize,  cubeMapSize,
         cubeMapSize, -cubeMapSize,  cubeMapSize
    };




    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}


void CubeMaps::operator=(const CubeMaps& cubeMaps)
{
    this->slot = cubeMaps.slot;
    this->height = cubeMaps.height;
    this->width = cubeMaps.width;
    this->ID = cubeMaps.ID;
    this->type = cubeMaps.type;
}


CubeMaps::CubeMaps(std::vector<std::string> allMapsFile) 
{

    type = GL_TEXTURE_CUBE_MAP;

    glGenTextures(1, &ID);
    glBindTexture(type, ID);
    unsigned char* data;


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
