#include "Window.h"

namespace Draug {

void Window::update() {
	pollEvents();
}

EventHandlerId Window::registerEventHandler(EventHandler handler) {
	EventHandlerId id = Event::getNextId();
	m_event_handlers[id] = handler;
	return id;
}

void Window::unregisterEventHandler(EventHandlerId id) {
	if (m_event_handlers.find(id) != m_event_handlers.end()) {
		m_event_handlers.erase(id);
	}
}

void Window::onEvent(const Event& event) {
	for (auto it : m_event_handlers) {
		it.second(event);
	}
}
}
