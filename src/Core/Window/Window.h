#pragma once

#include "Draug.h"
#include "Core/Event/Event.h"

namespace Draug {
struct WindowConfig;
class Window {
public:
	static Window* createWindow(const WindowConfig& config);

	Window() = default;
	Window(const Window& other) = delete;
	virtual ~Window() = default;

	virtual bool initialize(const WindowConfig& config) = 0;
	virtual void shutdown() = 0;

	void update();

	EventHandlerId registerEventHandler(EventHandler handler);
	void unregisterEventHandler(EventHandlerId id);

	virtual void* getNativeWindow() = 0;

protected:
	virtual void pollEvents() = 0;
	void onEvent(const Event& event);
private:
	std::unordered_map<EventHandlerId, EventHandler> m_event_handlers;
};
}
