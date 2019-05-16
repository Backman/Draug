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

private:
	GLFWwindow* m_window;
};
}
