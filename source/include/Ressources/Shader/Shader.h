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
#include<Light/PointLight/PointLight.h>
#include<Light/DirectionalLight/DirectionalLight.h>
#include<Light/SpothLight/SpothLight.h>

#include<LowRenderer/Material/Material.h>

class Shader : public IResource 
{
public:

    void Use() const;
    void Use();
    void UnUse();
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVector4(const std::string& name, const float* value) const;
    void SetMaxtrix(const std::string& name, const float* matrixValue) const;
    void SetVector3(const std::string& name, const float* value) const;
    void SetMaterial(const std::string& name, const Material& material) const ;
    GLuint GetId() const ;
 
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath, std::string shaderName);
    ~Shader();
protected:
     mutable std::unordered_map<std::string, GLint> m_UniformMap;
    GLint GetUnitform(const std::string& name) const ;
    GLuint m_ID;

};

#endif