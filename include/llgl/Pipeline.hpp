#pragma once
#include <memory>
#include <vector>
#include "llgl/Shader.hpp"

namespace llgl
{
class Shader;

class Pipeline
{
public:
    using ShaderPtr = std::shared_ptr<Shader>;
    using Shaders = std::vector<ShaderPtr>;

    Pipeline();
    ~Pipeline();

    void addShader(ShaderPtr shader);
    void bind();

private:
    unsigned int getShaderBitGlType(Shader::Type type);

    unsigned int pipelineId;
    Shaders shaders;
};


} // namespace llgl
