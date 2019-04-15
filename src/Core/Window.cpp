#include "draugpch.h"
#include "Window.h"
#include "WindowImpl.h"

namespace Draug {
	Window::Window() {
	}

	Window::~Window() {
		shutdown();
	}

	void Window::initialize(const WindowConfig& config) {
		s_window_impl = new details::WindowImpl();
		s_window_impl->initialize(config);
	}

	void Window::display() {
		s_window_impl->display();
	}

	void Window::shutdown() {
		if (s_window_impl == nullptr) {
			return;
		}
		s_window_impl->shutdown();
		delete s_window_impl;
		s_window_impl = nullptr;
	}
}
