#pragma once
#include "lve_window.hpp"
#include <stdexcept>

namespace lve {
	lve::LveWindow::LveWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name}
	{
		initWindow();
	}
	lve::LveWindow::~LveWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	void LveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create window surface");
		}
	}
	void LveWindow::initWindow()
	{
		glfwInit(); //initialize the glfw library
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}
	
}


