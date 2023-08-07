#include <Ressources/Texture/Texture.hpp>
#include<string>
#include<Ressources/Shader/Shader.h>
#include "External/Std_Image/std_image.h"
#include "App/App.h"

void Texture::Init()
{
    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}
Texture::Texture(const fs::path& FilePath) 
{
    path = FilePath.generic_string();
    type = GL_TEXTURE_2D;
    
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(path.c_str(), &width, &height, &nbrOfChannel, 0);


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

    format = other.format;

    width = other.width;
    height = other.height;
    nbrOfChannel = other.nbrOfChannel;
    path = other.path;
    return *this;
}









void Texture::BindTexture() const
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::UnBindTexture() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
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




