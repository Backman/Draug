#include "Window.h"

namespace Draug {

uint16_t Window::s_id_counter = 0;

EventCallbackId Window::subscribe_event(EventCallback callback) {
	return m_event_dispatcher.subscribe(callback);
}

void Window::unsubscribe_event(EventCallbackId id) {
	m_event_dispatcher.unsubscribe(id);
}

void Window::dispatch_event(Event& event) {
	m_event_dispatcher.dispatch(event);
}
}
