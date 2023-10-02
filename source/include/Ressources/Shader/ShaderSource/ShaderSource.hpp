#pragma once 
#include <string>
#include <fstream>
#include <sstream>
#include "Ressources/IResources/IResource.h"
enum class ShaderSourceType
{
	VERTEXSHADER,
	FRAGMENTSHADER,
	GEOMETRYSHADER
};



class ShaderSource : public IResource
{
public:

	void CompileShader();
	void InitResource() override;

	ShaderSource(const fs::path& FilePath);
	~ShaderSource();

	std::string ShaderName;
	unsigned int ShaderID;
	std::string ShaderCode;
	ShaderSourceType Shadertype;
private:
	std::string m_pathToSourceCode;
	
};

