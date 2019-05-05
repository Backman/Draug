#pragma once

#include "Core/Window/Window.h"

struct GLFWwindow;

namespace Draug {
class glfwWindow : public Window {
public:
	bool init(const WindowConfig& config) override;
	void shutdown() override;
	void beginFrame() override;
	void render() override;
	void endFrame() override;

private:
	GLFWwindow* m_window;
};
}
