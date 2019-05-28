#pragma once

#include "Core/Window/Window.h"

struct GLFWwindow;

namespace Draug {
class glfwWindow : public Window {
public:
	bool init(const WindowConfig& config) override;
	void shutdown() override;
	void begin_frame() override;
	void render() override;
	void end_frame() override;

	int get_width() const override;
	int get_height() const override;
	int get_framebuffer_width() const override;
	int get_framebuffer_height() const override;

private:
	static void glfw_windowCloseCallback(GLFWwindow* window);
	static void glfw_windowSizeCallback(GLFWwindow* window, int width, int height);
	static void glfw_windowPosCallback(GLFWwindow* window, int x_pos, int y_pos);
	static void glfw_keyCallback(GLFWwindow* window, int glfw_key, int scancode, int action, int mods);
	static void glfw_mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void glfw_cursorPosCallbac(GLFWwindow* window, double x, double y);
	static void glfw_scrollCallback(GLFWwindow* window, double x_scroll, double y_scroll);

	GLFWwindow* m_window;
};
}
