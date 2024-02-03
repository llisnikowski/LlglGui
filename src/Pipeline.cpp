#include "llgl/Pipeline.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "llgl/Shader.hpp"


namespace llgl
{


Pipeline::Pipeline()
{
    glCreateProgramPipelines(1, &this->pipelineId);
}

Pipeline::~Pipeline()
{
    glDeleteProgramPipelines(1, &this->pipelineId);
}

void Pipeline::addShader(ShaderPtr shader)
{
    auto it = shaders.begin();
    for(; it < shaders.end(); it++){
        if((*it)->getType() == shader->getType()){
            *it = shader;
            break;
        }
    }
    if(it == shaders.end()){
        shaders.push_back(shader);
    }

    glUseProgramStages(this->pipelineId, getShaderBitGlType(shader->getType()), shader->getId());
}

unsigned int Pipeline::getShaderBitGlType(Shader::Type type)
{
    switch (type)
    {
    case Shader::Type::VERTEX:
        return GL_VERTEX_SHADER_BIT;
    case Shader::Type::GEOMETRY:
        return GL_GEOMETRY_SHADER_BIT;
    case Shader::Type::FRAGMENT:
        return GL_FRAGMENT_SHADER_BIT;
    default:
        return {};
    }
}

void Pipeline::bind()
{
    glBindProgramPipeline(this->pipelineId);
}

} // namespace llgl

