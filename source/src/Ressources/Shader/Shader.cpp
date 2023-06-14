#include <Ressources/Shader/Shader.h>







Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath,std::string shaderName)
{



    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath); 
        gShaderFile.open(geometryPath);

        std::stringstream vShaderStream, fShaderStream, gShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        gShaderStream << gShaderFile.rdbuf();

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        gShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        geometryCode = gShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {

        Debug::Log->LogWarning(shaderName + " :  ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ \n ");
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();




    // 2. compile shaders
    unsigned int vertex, fragment,geometry;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        Debug::Log->LogWarning(shaderName + " : ERROR::SHADER::VERTEX::COMPILATION_FAILED" + '\n' + std::to_string(*infoLog));
    }
    else
    {
        Debug::Log->LogGood(shaderName + " : VERTEX::PROGRAM::COMPILATION_SUCCED");

    }

    // geometry Shader
    geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &gShaderCode, NULL);
    glCompileShader(geometry);
    // print compile errors if any
    glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(geometry, 512, NULL, infoLog);
        Debug::Log->LogWarning(shaderName + " : ERROR::SHADER::GEOMETRY::COMPILATION_FAILED" + '\n' + std::to_string(*infoLog));
    }
    else
    {
        Debug::Log->LogGood(shaderName + " : GEOMETRY::PROGRAM::COMPILATION_SUCCED");

    }




    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        Debug::Log->LogWarning(shaderName + " :ERROR::SHADER::FRAG::COMPILATION_FAILED" + '\n' + std::to_string(*infoLog));
    }
    else
    {
        Debug::Log->LogGood(shaderName + " : FRAG::PROGRAM::COMPILATION_SUCCED" + shaderName);

    }

    
    // shader Program
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    //glAttachShader(m_ID, geometry);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    // print linking errors if any
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        Debug::Log->LogWarning(shaderName + "ERROR::SHADER::PROGRAM::LINKING_FAILED" + std::to_string(*infoLog));
    }
    else
    {
        Debug::Log->LogGood(shaderName + " : SHADER::PROGRAM::LINKED");

    }



    // delete Shader cause we liked them before so there no longer nessecery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(geometry);

}






void Shader::Use()
{
    glUseProgram(m_ID);
}

void Shader::Use() const
{
    glUseProgram(m_ID);
}

void Shader::UnUse()
{
    glUseProgram(0);
}

void Shader::SetBool(const std::string& name, bool value) const
{
    int currentLoc = GetUnitform(name.c_str());
    glUniform1i(currentLoc, (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
    int currentLoc = GetUnitform(name.c_str());

    glUniform1i(currentLoc, value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    int currentLoc = GetUnitform(name.c_str());

    glUniform1f(currentLoc, value);

}

void Shader::SetVector4(const std::string& name, const float* value) const
{


    int currentLoc = GetUnitform(name.c_str());
    glUniform4fv(currentLoc, 1, value);
}

void Shader::SetMaxtrix(const std::string& name, const float* matrixValue) const
{

    int currentLoc = GetUnitform(name.c_str());
    glUniformMatrix4fv(currentLoc, 1, GL_TRUE, matrixValue);
}

void Shader::SetVector3(const std::string& name, const float* value) const
{
    int currentLoc = GetUnitform(name.c_str());

    glUniform3fv(currentLoc, 1, value);
}

void Shader::SetMaterial(const std::string& name, const Material& material) const
{
    SetInt("material.diffuse", material.diffuse);
    SetInt("material.specular", material.specular);
    SetFloat("material.shininess", material.shininess);

}

GLuint Shader::GetId() const
{
    return m_ID;
}






Shader::~Shader()
{
    glDeleteShader(m_ID);
}

GLint Shader::GetUnitform(const std::string& name) const
{

    if (m_UniformMap.find(name) != m_UniformMap.end())
    {
        return m_UniformMap[name];
    }

    GLint location = glGetUniformLocation(m_ID, name.c_str());
    m_UniformMap[name] = location;

    return location;
}

