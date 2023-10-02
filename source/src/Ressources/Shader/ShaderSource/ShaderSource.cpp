#include "Ressources/Shader/ShaderSource/ShaderSource.hpp"
#include "Core/Debug/Debug.h"
#include <glad/glad.h>

void ShaderSource::CompileShader()
{
	std::ifstream ShaderFile;
	ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		ShaderFile.open(m_pathToSourceCode);
		std::stringstream ShaderStream;
		ShaderStream << ShaderFile.rdbuf();
		ShaderFile.close();
		ShaderCode = ShaderStream.str();
		
	}catch(std::ifstream::failure e)
	{
		LOG(" :  ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ \n ",STATELOG::CRITICALERROR);
	}
}

void ShaderSource::InitResource()
{
	int success;
	char infoLog[512];

	const char* Shader = ShaderCode.c_str();


	switch (Shadertype)
	{
	case ShaderSourceType::VERTEXSHADER:
		ShaderID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderSourceType::FRAGMENTSHADER:
		ShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case ShaderSourceType::GEOMETRYSHADER:
		ShaderID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	default:
		break;
	}

	// vertex Shader
	glShaderSource(ShaderID, 1, &Shader, NULL);
	glCompileShader(ShaderID);
	// print compile errors if any
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(ShaderID, 512, NULL, infoLog);
		LOG(ShaderName + " : ERROR::SHADER::VERTEX::COMPILATION_FAILED" + '\n' + std::to_string(*infoLog), STATELOG::CRITICALERROR);

	}
	else
	{
		LOG(ShaderName + " : VERTEX::PROGRAM::COMPILATION_SUCCED \n", STATELOG::GOOD);
	}
}

ShaderSource::ShaderSource(const fs::path& FilePath) 
{
	m_pathToSourceCode = FilePath.generic_string();
	std::string extensionOfShader = FilePath.extension().generic_string();
	
	if (extensionOfShader == ".vert")
	{
		Shadertype = ShaderSourceType::VERTEXSHADER;
	}
	if (extensionOfShader == ".frag")
	{
		Shadertype = ShaderSourceType::FRAGMENTSHADER;
	}

	if (extensionOfShader == ".geom")
	{
		Shadertype = ShaderSourceType::GEOMETRYSHADER;
	}
	ShaderName = FilePath.filename().generic_string();
	CompileShader();
}

ShaderSource::~ShaderSource()
{
}
