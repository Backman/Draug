#include "draugpch.h"
#include "Window.h"
#include "WindowImpl/WindowImpl.h"

namespace Draug {
	Window::Window() {
	}

	Window::~Window() {
		shutdown();
	}

	void Window::initialize(const WindowConfig& config) {
		m_impl = new details::WindowImpl();
		m_impl->initialize(config);
	}

	void Window::update() {
		m_impl->update();
		m_impl->processEvents();
	}

	void Window::shutdown() {
		if (m_impl == nullptr) {
			return;
		}
		m_impl->shutdown();
		delete m_impl;
		m_impl = nullptr;
	}

	EventHandlerId Window::registerEventHandler(EventHandler handler) {
		return m_impl->registerEventHandler(handler);
	}

	void Window::unregisterEventHandler(EventHandlerId id) {
		m_impl->unregisterEventHandler(id);
	}
}
