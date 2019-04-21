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

	EventCallbackId subscribeEvent(EventCallback callback);
	void unsibscribEvent(EventCallbackId id);
	inline EventDispatcher* getEventDispatcher() { return &m_event_dispatcher; }

	virtual void* getNativeWindow() = 0;

protected:
	virtual void pollEvents() = 0;
	void dispatchEvent(const Event& event);
private:
	EventDispatcher m_event_dispatcher;
};
}
