#include "llgl/RectObj.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string_view>
#include <iostream>
#include <llgl/Shader.hpp>

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
}


GLuint compileShader(const GLchar* _source, GLenum _stage, const std::string& _msg);


bool RectObj::init()
{
    pipeline.addShader(std::make_shared<Shader>(Shader::Type::VERTEX
        ,vert
    ));
    pipeline.addShader(std::make_shared<Shader>(Shader::Type::GEOMETRY
        ,geom
    ));
    pipeline.addShader(std::make_shared<Shader>(Shader::Type::FRAGMENT
        ,frag
    ));


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


    glBindVertexArray(vao);

    return true;
}







bool RectObj::draw()
{
    pipeline.bind();
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, 1);

    return false;
}

bool RectObj::operator==(llgl::RectObj rhs)
{
	return this->point == rhs.point && this->size == rhs.size;
}

} // namespace llgl
