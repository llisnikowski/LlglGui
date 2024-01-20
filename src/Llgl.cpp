#include "llgl/Llgl.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace llgl
{


Llgl::Llgl()
{
}

Llgl::~Llgl()
{
	glfwTerminate();
}

bool Llgl::init()
{
	if(!this->window) return false;

	if(!this->glfwInit()) return false;
	if(!this->window->init()) return false;
	if(!this->loadGlad()) return false;
	return true;
}

bool Llgl::glfwInit()
{
	::glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	
	return true;
}

bool Llgl::loadGlad()
{
	gladLoadGL();
	return true;
}

void Llgl::setWindow(std::shared_ptr<Window> window)
{
	this->window = window;
}

std::shared_ptr<Window> Llgl::getWindow()
{
	return this->window;
}

int Llgl::run()
{
	if(!this->window) return 1;
	if(!this->init()) return 2;

	while (!glfwWindowShouldClose(this->window->getWindow()))
    {

		const Color &color = this->window->getBackgroundColor();
        glClearColor(color.r, color.g, color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

	// 	for(auto &object : this->objects){
	// 		auto objectLock = object.lock();
	// 		if(objectLock == nullptr) continue;
	// 		objectLock->draw();
	// 	}

        glfwSwapBuffers(this->window->getWindow());
        glfwPollEvents();
    }

	return true;
}



} // namespace llgl
