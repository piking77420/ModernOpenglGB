#pragma once
#include <iostream>
#include<glad/glad.h>
#include<Ressources/IResources/IResource.h>

class Shader;


// DIFFUSE 0 
// SPECULAR 1 




class Texture : public IResource
{
public:

	
	
	void Init() override;
	void BindTexture() const;
	void UnBindTexture()const;
	void TextureShaderUniform(const Shader& shader, const char* uniform, GLuint unit);

	GLuint ID;

	Texture(const fs::path& FilePath);
	Texture();

	~Texture();

	static GLuint GetFormat(int nbrOfChannel);
	void operator=(const Texture& other);

protected:
	GLuint format;
	int width;
	int height;
	int nbrOfChannel;
	unsigned char* data;

};
