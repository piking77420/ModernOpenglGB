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
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(type, ID);

    glTexImage2D(type, 0, format, width, height, 0, format, PixelType, data);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(type);
    stbi_image_free(data);

}
Texture::Texture(const std::string& ImagePath, GLenum TextureType, GLenum pixelType)
{
    imagePath = ImagePath;

    type = TextureType;
    PixelType = pixelType;

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(ImagePath.c_str(), &width, &height, &nbrOfChannel, 0);


  
    format = GetFormat(nbrOfChannel);

    if (!data)
    {
        std::cout << "Fail to load texture" << std::endl;
    }


 

   
}

Texture::Texture(const std::string& ImagePath)
{
    imagePath = ImagePath;
    PixelType = GL_UNSIGNED_BYTE;
    type = GL_TEXTURE_2D;
    std::cout << imagePath << std::endl;

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(ImagePath.c_str(), &width, &height, &nbrOfChannel, 0);



    format = GetFormat(nbrOfChannel);

    if (!data)
    {
        std::cout << "Fail to load texture" << std::endl;
    }


   

}

Texture::Texture(const std::string& ImagePath, GLenum TextureType, GLenum pixelType, bool isNormalMap)
{
    type = TextureType;

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(ImagePath.c_str(), &width, &height, &nbrOfChannel, 0);


    if (!isNormalMap)
        format = GetFormat(nbrOfChannel);
    else
        format = GL_RGB;


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
    if(App::GammaCorrection)
    {
        if (nbrOfChannel == 1)
        {
            return GL_RED;
        }
        else if (nbrOfChannel == 3)
        {
            return GL_SRGB;
        }
        else if (nbrOfChannel == 4)
        {
            return GL_SRGB_ALPHA;
        }
    }
    else
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
    }
    

    return GL_RGB;

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





