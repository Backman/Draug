#pragma once

#include "Core/Window/Window.h"

struct GLFWwindow;

namespace Draug {
namespace impl {
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
	static void glfw_window_close_callback(GLFWwindow* window);
	static void glfw_window_size_callback(GLFWwindow* window, int width, int height);
	static void glfw_window_pos_callback(GLFWwindow* window, int x_pos, int y_pos);
	static void glfw_key_callback(GLFWwindow* window, int glfw_key, int scancode, int action, int mods);
	static void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void glfw_cursor_pos_callbac(GLFWwindow* window, double x, double y);
	static void glfw_scroll_callback(GLFWwindow* window, double x_scroll, double y_scroll);

	GLFWwindow* m_window;
};
}
}
