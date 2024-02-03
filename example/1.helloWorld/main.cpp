#include "llgl/Llgl.hpp"
#include "llgl/Window.hpp"
#include "llgl/RectObj.hpp"
#include <iostream>



int main()
{
    llgl::Llgl app;
    auto window = std::make_shared<llgl::Window>("Hello World", llgl::Size{800, 600});
    app.setWindow(window);
    window->setBackgroundColor(llgl::Color{0.2, 0.4, 0.8});
    app.init();
    

    app.add(std::make_shared<llgl::RectObj>(llgl::Point{30, 30}, llgl::Size{100, 100}));

    return app.run();
}

