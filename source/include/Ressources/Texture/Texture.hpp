#pragma once
#include <iostream>
#include<glad/glad.h>
#include<Ressources/IResources/IResource.h>

class Shader;


// DIFFUSE 0 
// SPECULAR 1 

enum TextureFlags {
	NONEFLAG = 0,  // 1
	HDR = 1,  // 1
};




class Texture : public IResource
{
public:

	
	
	void InitResource() override;
	virtual void BindTexture() const;
	virtual void UnBindTexture()const;
	virtual void TextureShaderUniform(const Shader& shader, const char* uniform, GLuint unit);

	GLuint ID;

	Texture(const fs::path& FilePath);
	Texture(const fs::path& FilePath, TextureFlags flags);

	Texture();

	virtual ~Texture();

	static GLuint GetFormat(int nbrOfChannel);
	void operator=(const Texture& other);

	TextureFlags flags;

protected:
	GLuint format;
	int width;
	int height;
	int nbrOfChannel;
	unsigned char* datac;
	float* dataf;

};
