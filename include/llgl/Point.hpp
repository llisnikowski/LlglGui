#pragma once 
#include <cstddef>

namespace llgl {

struct Point
{
    constexpr Point(int x, int y);
    constexpr Point();

    int x;
    int y;
};


//-----------------------

constexpr Point::Point(int x, int y)
:x{x}, y{y}
{}


constexpr Point::Point()
:x{0}, y{0}
{}


} // namespace llgl

constexpr bool operator==(llgl::Point rhs, llgl::Point lhs)
{
	return rhs.x == lhs.x && rhs.y == lhs.y;
}

