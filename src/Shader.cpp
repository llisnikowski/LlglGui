#include "llgl/Shader.hpp"
#include <iostream>


namespace llgl
{

Shader::Shader(Type type)
:type{type}
{
}

Shader::~Shader()
{
    if(shaderId)
    glDeleteProgram(shaderId);
}

bool Shader::compile(const char *shader)
{
    int success = 0;
    this->shaderId = glCreateShaderProgramv(
        static_cast<unsigned int>(this->type), 1, &shader);
    glGetProgramiv(this->shaderId, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        std::string log;
        log.resize(1024);
        glGetProgramInfoLog(this->shaderId, log.size(), nullptr, &log.front());
        std::cout << "ERROR SHADER: " << this->getTypeStr() 
                  << " compilation failed:" << log << std::endl;
        return false;
    }
    return true;
}

unsigned int Shader::getId()
{
    return this->shaderId;
}

std::string Shader::getTypeStr()
{
    switch (this->type)
    {
    case Type::VERTEX:
        return "Vertex";
    case Type::GEOMETRY:
        return "Geometry";
    case Type::FRAGMENT:
        return "Fragment";
    default:
        return "Unknown";
    }
}


} // namespace llgl

