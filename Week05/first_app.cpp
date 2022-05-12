#include "first_app.hpp"

namespace lve {
	void FirstApp::run()
	{
		while (!lveWindow.shouldClose()) {
			glfwPollEvents(); //while our windows does not want to close hold window events, like clicks
		}
	}
}