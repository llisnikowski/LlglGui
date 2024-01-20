#pragma once
#include "llgl/Window.hpp"
#include <memory>

namespace llgl
{
class Window;

class Llgl
{
public:
    Llgl();
    ~Llgl();

    void setWindow(std::shared_ptr<Window> window);
    std::shared_ptr<Window> getWindow();
    int run();

private:
    bool init();
    bool glfwInit();
    bool loadGlad();


    std::shared_ptr<Window> window;
};

} // namespace llgl
