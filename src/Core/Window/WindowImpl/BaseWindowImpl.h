#pragma once

#include "draugpch.h"
#include "Core/Window/WindowConfig.h"
#include "Core/Event/Event.h"

namespace Draug {
namespace details {
class BaseWindowImpl {
protected:
	std::unordered_map<EventHandlerId, EventHandler> m_event_handlers;
	//std::vector<Event> m_pending_events;

public:
	BaseWindowImpl();
	virtual ~BaseWindowImpl();

	virtual void initialize(const WindowConfig& config) = 0;
	virtual void update();
	virtual void processEvents();
	virtual void shutdown();

	virtual EventHandlerId registerEventHandler(EventHandler handler);
	virtual void unregisterEventHandler(EventHandlerId id);

protected:
	void dispatchEvent(const Event& e);
};
}
}
