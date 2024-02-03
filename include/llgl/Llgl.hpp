#pragma once
#include "llgl/Window.hpp"
#include <memory>
#include <vector>

namespace llgl
{
class Window;
class Object;

class Llgl
{
public:
    Llgl();
    ~Llgl();

    void setWindow(std::shared_ptr<Window> window);
    std::shared_ptr<Window> getWindow();

    void add(std::shared_ptr<Object> obj);

    int run();

    bool init();
private:
    bool glfwInit();
    bool loadGlad();


    std::shared_ptr<Window> window;
    std::vector<std::shared_ptr<Object>> objects;
};

} // namespace llgl
