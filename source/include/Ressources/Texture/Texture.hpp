#pragma once
#include <iostream>
#include<glad/glad.h>
#include<Ressources/IResources/IResource.h>

class Shader;


// DIFFUSE 0 
// SPECULAR 1 

enum TextureType
{
	DIFFUSE,
	SPECULAR,
	HEIGHT,
	AMBIENT
};




class Texture : public IResource
{
public:

	
	
	void Init() override;
	void BindTexture() const;
	void UnBindTexture()const;
	void DeleteTexture();
	void TextureShaderUniform(const Shader& shader, const char* uniform, GLuint unit);

	GLuint ID;
	std::string type;
	std::string path;


	int width;
	int height;
	int nbrOfChannel;
	unsigned char* data;


	Texture(const fs::path& FilePath);
	Texture();

	~Texture();

	static GLuint GetFormat(int nbrOfChannel);
	Texture& operator=(const Texture& other);

protected:
	GLuint format;

};
