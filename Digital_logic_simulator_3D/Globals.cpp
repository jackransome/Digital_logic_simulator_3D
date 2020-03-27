#include "Globals.h"

namespace globals
{
	using std::make_shared;

	Graphics gfx;
	Input input;

	const float dt = 1000000.0f / 60.0f;
	const float dtSeconds = 1.0f / 60.0f;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		globals::input.key_callback(key, scancode, action, mods);
	}

	void mouse_button_callback(GLFWwindow* window, int key, int action, int mods) {
		globals::input.mouse_button_callback(key, action, mods);
	}

	void window_focus_callback(GLFWwindow* window, int focused) {
		globals::input.window_focus_callback(focused);
	}

	void globalInit()
	{
		gfx.init();
		input.init(globals::gfx.getWindowPointer());
		glfwSetKeyCallback(globals::gfx.getWindowPointer(), key_callback);
		glfwSetMouseButtonCallback(globals::gfx.getWindowPointer(), mouse_button_callback);
		glfwSetWindowFocusCallback(globals::gfx.getWindowPointer(), window_focus_callback);
	}
}