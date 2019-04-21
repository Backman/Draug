#include "Window.h"

namespace Draug {

void Window::update() {
	pollEvents();
}

EventCallbackId Window::subscribeEvent(EventCallback callback) {
	return m_event_dispatcher.subscribe(callback);
}

void Window::unsibscribEvent(EventCallbackId id) {
	m_event_dispatcher.unsubscribe(id);
}

void Window::dispatchEvent(const Event& event) {
	m_event_dispatcher.dispatch(event);
}
}
