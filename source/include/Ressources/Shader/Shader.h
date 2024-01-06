#pragma once


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

enum SHADERFLAG : int
{
    NONE = 0,
    VERTEX = 0 << 1,
    FRAGMENT = 0 << 2,
    GEOMETRY = 0 << 3,
};

class ShaderSource;
class ResourcesManager;

class Shader : public IResource 
{
public:

    SHADERFLAG shaderFlag;

    void Use() const;
    void Use();
    void UnUse();
    void UnUse() const;
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVector4(const std::string& name, const float* value) const;
    void SetMatrix(const std::string& name, const float* matrixValue) const;
    void SetVector3(const std::string& name, const float* value) const;

 
    GLuint GetId() const ;
    void InitResource() override;

    // we assume that There is Fragment vertex and geometry shader is this folder
    Shader(const fs::path& FilePath);

    static SHADERFLAG GetShaderFlagsInDirectory(const fs::path& FilePath, Shader& shader);
    


    ~Shader();
protected:
    mutable std::unordered_map<std::string, GLint> m_UniformMap;
    GLint GetUnitform(const std::string& name) const ;
    GLuint m_ID;

    std::string m_vShaderCode;
    std::string m_fShaderCode;
    std::string m_gShaderCode;
    std::string mShaderName;

private:

    static void LoadShaderFileInString(std::string& string, const fs::path& FilePath);
};

