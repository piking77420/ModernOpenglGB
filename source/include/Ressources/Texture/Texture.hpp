#pragma once
#include <iostream>
#include<glad/glad.h>
#include<Ressources/IResources/IResource.h>

class Shader;



class Texture : public IResource
{
public:

	
	
	void BindTexture() const;
	void UnBindTexture()const;
	void DeleteTexture();
	void TextureShaderUniform(const Shader& shader, const char* uniform, GLuint unit);

	GLuint ID;
	GLenum type;
	GLenum PixelType;

	GLuint format;
	int slot;

	int width;
	int height;
	int nbrOfChannel;

	unsigned char* data;
	void Init() override;

	Texture(std::string ImagePath);

	Texture();
	~Texture();


protected:
	void IncrementTexture();
	static int GlobTextureNbr;
	std::string imagePath;
	const std::string SLOT = "GL_TEXTURE";
	GLuint GetFormat(int nbrOfChannel);
};
