#include "llgl/Llgl.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "llgl/Object.hpp"
#include <iostream>

namespace llgl
{


Llgl::Llgl()
{
}

Llgl::~Llgl()
{
	for(auto &object : this->objects){
		object.reset();
	}
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
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

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

void Llgl::add(std::shared_ptr<Object> obj)
{
	this->objects.push_back(obj);
}


int Llgl::run()
{
	if(!this->window) return 1;

	while (!glfwWindowShouldClose(this->window->getWindow()))
    {
		if (glfwGetKey(this->window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window->getWindow(), true);

		const Color &color = this->window->getBackgroundColor();
        glClearColor(color.r, color.g, color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		for(auto &object : this->objects){
			if(object == nullptr) continue;
			object->draw();
		}

        glfwSwapBuffers(this->window->getWindow());
        glfwPollEvents();
    }	

	return 0;
}



} // namespace llgl
