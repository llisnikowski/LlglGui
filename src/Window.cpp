#include "llgl/Window.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace llgl
{


Window::Window(std::string name, Size size)
:name{std::move(name)}, size{size}, color{1.0, 1.0, 1.0}, window{nullptr}
{
}

Window::~Window()
{
    if(this->window) glfwDestroyWindow(this->window);
}

bool Window::init()
{
    if(this->size.width <= 0 || this->size.height <= 0) return false;
    this->window = glfwCreateWindow(this->size.width, this->size.height
        ,this->name.c_str(), nullptr, nullptr);
    if(this->window == nullptr) return false;
    glfwMakeContextCurrent(this->window);
    
    return true;
}


std::string Window::getName() const
{
    return this->name;
}

Size Window::getSize() const
{
    return this->size;
}

void Window::setSize(Size size)
{
    this->size = size;
}

void Window::setName(std::string name)
{
    this->name = name;
}

Color Window::getBackgroundColor() const
{
    return this->color;
}

void Window::setBackgroundColor(Color color)
{
    this->color = color;
}



} // namespace llgl
