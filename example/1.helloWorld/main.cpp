#include "llgl/Llgl.hpp"
#include "llgl/Window.hpp"

int main()
{
    llgl::Llgl app;
    auto window = std::make_shared<llgl::Window>("Hello World", llgl::Size{800, 600});
    app.setWindow(window);

    window->setBackgroundColor(llgl::Color{0.2, 0.4, 0.8});
    
    return app.run();
}