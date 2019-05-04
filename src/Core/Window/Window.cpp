#include "Window.h"

namespace Draug {

uint16_t Window::s_id_counter = 0;

EventCallbackId Window::subscribeEvent(EventCallback callback) {
	return m_event_dispatcher.subscribe(callback);
}

void Window::unsubscribEvent(EventCallbackId id) {
	m_event_dispatcher.unsubscribe(id);
}

void Window::dispatchEvent(Event& event) {
	m_event_dispatcher.dispatch(event);
}
}
