#include <Ressources/Texture/Texture.hpp>
#include<string>
#include<Ressources/Shader/Shader.h>
#include "External/Std_Image/std_image.h"
#include "App/App.h"

int Texture::GlobTextureNbr = 0;
void Texture::Init()
{

    IncrementTexture();

    glGenTextures(1, &ID);
    glBindTexture(type, ID);

    glTexImage2D(type, 0, format, width, height, 0, format, PixelType, data);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(type);
    stbi_image_free(data);


}
Texture::Texture(const fs::path& FilePath) 
{
    imagePath = FilePath.generic_string();
    PixelType = GL_UNSIGNED_BYTE;
    type = GL_TEXTURE_2D;
    
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(imagePath.c_str(), &width, &height, &nbrOfChannel, 0);


    format = GetFormat(nbrOfChannel);

    if (!data)
    {
        std::cout << "Fail to load texture" << std::endl;
    }


   

}

Texture::Texture()
{
  
}




Texture::~Texture()
{
}

void Texture::IncrementTexture()
{
    slot = GlobTextureNbr;
    GlobTextureNbr++;
}

GLuint Texture::GetFormat(int nbrOfChannel)
{
   
    

        if (nbrOfChannel == 1)
        {
            return GL_RED;
        }
        else if (nbrOfChannel == 3)
        {
            return GL_RGB;
        }
        else if (nbrOfChannel == 4)
        {
            return GL_RGBA;
        }
    
    

    return GL_RGB;

}

Texture& Texture::operator=(const Texture& other)
{
    ID = other.ID;
    type = other.type;
    PixelType = other.PixelType;

    format = other.format;
    slot = other.slot;

    width = other.width;
    height = other.height;
    nbrOfChannel = other.nbrOfChannel;
    imagePath = other.imagePath;
    return *this;
}









void Texture::BindTexture() const
{
    glBindTexture(type, ID);
}

void Texture::UnBindTexture() const
{
    glBindTexture(type, 0);
}

void Texture::DeleteTexture()
{
    glDeleteTextures(1, &ID);
}

void Texture::TextureShaderUniform(const Shader& shader, const char* uniform, GLuint unit)
{
    GLuint texUni = glGetUniformLocation(shader.GetId(), uniform);

    shader.Use();

    glUniform1i(texUni, unit);


}




