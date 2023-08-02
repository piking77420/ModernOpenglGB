#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> 
#include <Ressources/IResources/IResource.h>
#include<unordered_map>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <Vector4.h>
#include <Vector3.h>


#include<LowRenderer/Material/Material.h>



class ShaderSource;

class Shader : public IResource 
{
public:

    

    void Use() const;
    void Use();
    void UnUse();
    void UnUse() const;
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVector4(const std::string& name, const float* value) const;
    void SetMaxtrix(const std::string& name, const float* matrixValue) const;
    void SetVector3(const std::string& name, const float* value) const;
    void SetMaterial(const std::string& name, const Material& material) const ;
    GLuint GetId() const ;
 
    void Init() override;

    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath, std::string shaderName);
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(const ShaderSource& vertexShader, const ShaderSource& fragmentShader);
    Shader(const ShaderSource& vertexShader, const ShaderSource& fragmentShader , const ShaderSource& GeometryShader);


    ~Shader();
protected:
     mutable std::unordered_map<std::string, GLint> m_UniformMap;
    GLint GetUnitform(const std::string& name) const ;
    GLuint m_ID;

    std::string m_vShaderCode;
    std::string m_fShaderCode;
    std::string m_gShaderCode;
    std::string mShaderName;


};

#endif