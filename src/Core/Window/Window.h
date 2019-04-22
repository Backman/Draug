#pragma once

#include "Draug.h"
#include "Core/Event/Event.h"
#include "Core/Window/WindowConfig.h"

namespace Draug {
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

	inline uint32 getWidth() const { return m_config.width; }
	inline uint32 getHeight() const { return m_config.height; }
	inline const char* getTitle() const { return m_config.title; }
	inline bool isFullscreen() const { return m_config.fullscreen; }

protected:
	virtual void pollEvents() = 0;
	void dispatchEvent(const Event& event);

protected:
	WindowConfig m_config;
private:
	EventDispatcher m_event_dispatcher;
};
}
