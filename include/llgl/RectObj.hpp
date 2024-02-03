#pragma once
#include "llgl/Point.hpp"
#include "llgl/Size.hpp"
#include "llgl/Object.hpp"

namespace llgl
{

class RectObj : public Object
{
public:
    RectObj(Point point, Size size);
    RectObj(Size size);
    RectObj();
    ~RectObj();

    bool draw() override;

    bool operator==(llgl::RectObj rhs);
private:

    bool init();

    Point point;
    Size size;

    unsigned int pipeline{};
    unsigned int vertexShader{};
    unsigned int geometryShader{};
    unsigned int fragmentShader{};
    unsigned int vao{};
    unsigned int vbo{};
};






} // namespace llgl

