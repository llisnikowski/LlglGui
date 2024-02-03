#include "llgl/RectObj.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string_view>
#include <iostream>

const char* vert =
R"vertex_shader(#version 450 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 size;

out gl_PerVertex{
    vec4 gl_Position;
};
out VS_OUT{
    vec2 size;
} vs_out;

void main()
{
    gl_Position = vec4(pos, 0, 1.0);
    vs_out.size = size;
}
)vertex_shader";

const char* geom =
R"geometry_shader(#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in gl_PerVertex{
    vec4 gl_Position;
} gl_in[];
in VS_OUT{
    vec2 size;
} vs_in[];

out gl_PerVertex{
    vec4 gl_Position;
};

void main(){
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(vs_in[0].size.x, 0.0, 0.0, 0.0); 
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.0, vs_in[0].size.y, 0.0, 0.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(vs_in[0].size , 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}
)geometry_shader";

const char* frag =
R"frag_shader(#version 450 core

out vec4 FragColor;

void main(){
    FragColor = vec4(0.5, 0.5, 0.0, 1.0);
}
)frag_shader";


namespace llgl
{


RectObj::RectObj(Point point, Size size)
:point{point}, size{size}
{
    init();
}

RectObj::RectObj(Size size)
:point{}, size{size}
{
    init();
}

RectObj::RectObj()
:point{}, size{}
{
    init();
}



RectObj::~RectObj()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgramPipelines(1, &pipeline);
    glDeleteProgram(vertexShader);
    glDeleteProgram(geometryShader);
    glDeleteProgram(fragmentShader);
}


GLuint compileShader(const GLchar* _source, GLenum _stage, const std::string& _msg);


bool RectObj::init()
{
    int success = 0;

    vertexShader = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vert);
    glGetProgramiv(vertexShader, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        std::string log;
        log.resize(1024);
        glGetProgramInfoLog(vertexShader, log.size(), nullptr, &log.front());
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
        return false;
    }

    geometryShader = glCreateShaderProgramv(GL_GEOMETRY_SHADER, 1, &geom);
    glGetProgramiv(geometryShader, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        std::string log;
        log.resize(1024);
        glGetProgramInfoLog(geometryShader, log.size(), nullptr, &log.front());
        std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << log << std::endl;
        return false;
    }

    fragmentShader = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &frag);
    glGetProgramiv(fragmentShader, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        std::string log;
        log.resize(1024);
        glGetProgramInfoLog(fragmentShader, log.size(), nullptr, &log.front());
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
        return false;
    }

    glCreateProgramPipelines(1, &pipeline);
    glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vertexShader);
    glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, fragmentShader);
    glUseProgramStages(pipeline, GL_GEOMETRY_SHADER_BIT, geometryShader);


    float vertices[] = {
        -0.5f, -0.5f,
        0.8f, 0.5f
    };

    glCreateVertexArrays(1, &vao);

    glCreateBuffers(1, &vbo);
    glNamedBufferStorage(vbo, sizeof(vertices), vertices, 0);

    constexpr GLuint ATTR_POS = 0u;
    glEnableVertexArrayAttrib(vao, ATTR_POS);
    glVertexArrayAttribFormat(vao, ATTR_POS, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, ATTR_POS, vbo, 0, 4*sizeof(float));
    glVertexArrayAttribBinding(vao, ATTR_POS, ATTR_POS);

    constexpr GLuint ATTR_COLOR = 1u;
    glEnableVertexArrayAttrib(vao, ATTR_COLOR);
    glVertexArrayAttribFormat(vao, ATTR_COLOR, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, ATTR_COLOR, vbo, 2*sizeof(float), 4 * sizeof(float));
    glVertexArrayAttribBinding(vao, ATTR_COLOR, ATTR_COLOR);


    glBindProgramPipeline(pipeline);
    glBindVertexArray(vao);

    return true;
}







bool RectObj::draw()
{

    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, 1);

    return false;
}

bool RectObj::operator==(llgl::RectObj rhs)
{
	return this->point == rhs.point && this->size == rhs.size;
}

} // namespace llgl
