#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <type_traits>


namespace llgl
{

class Shader
{
public:
    enum class Type {
        UNKNOWN,
        VERTEX = GL_VERTEX_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER
    };
    Shader(Type type);
    template <typename T>
    Shader(Type type, T &&shader);
    ~Shader();

    template <typename T>
    bool compile(T &&shader);
    bool compile(const char *shader);

    Type getType(){return this->type;}
    unsigned int getId();

private:
    std::string getTypeStr();

    Type type = {};
    unsigned int shaderId = {};
};



template <typename T>
Shader::Shader(Type type, T &&shader)
:type{type}
{
    if constexpr(std::is_convertible_v<T, const char*>){
        this->compile(shader);
    }
    else{
        this->compile(std::forward(shader));
    }
}

template <typename T>
bool Shader::compile(T &&shader)
{
    return this->compile(shader.c_str());
}

} // namespace llgl

