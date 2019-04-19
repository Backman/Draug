#include "draugpch.h"
#include "BaseWindowImpl.h"

namespace Draug {
namespace details {
BaseWindowImpl::BaseWindowImpl() {
}

BaseWindowImpl::~BaseWindowImpl() {
}

void BaseWindowImpl::update() {
	processEvents();
}

void BaseWindowImpl::processEvents() {
	return;
	//if (m_pending_events.size() == 0) {
	//	return;
	//}

	//for (size_t i = 0; i < m_pending_events.size(); i++) {
	//	dispatchEvent(m_pending_events[i]);
	//}
	//m_pending_events.clear();
}

void BaseWindowImpl::shutdown() {
}

EventHandlerId BaseWindowImpl::registerEventHandler(EventHandler handler) {
	EventHandlerId id = Event::getNextId();
	m_event_handlers.emplace(id, handler);
	return id;
}

void BaseWindowImpl::unregisterEventHandler(EventHandlerId id) {
	m_event_handlers.erase(id);
}

void BaseWindowImpl::dispatchEvent(const Event& e) {
	for (auto it : m_event_handlers) {
		it.second(e);
	}
}
}
}
