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

	inline virtual bool init(const WindowConfig& config) {
		m_id = s_id_counter++;
		m_config = config;
		return true;
	}
	virtual void shutdown() = 0;

	virtual void beginFrame() = 0;
	virtual void render() = 0;
	virtual void endFrame() = 0;

	EventCallbackId subscribeEvent(EventCallback callback);
	void unsubscribEvent(EventCallbackId id);
	inline EventDispatcher* getEventDispatcher() { return &m_event_dispatcher; }

	inline void* getNativeWindow() { return m_native_window; }

	inline int getWidth() const { return m_config.width; }
	inline int getHeight() const { return m_config.height; }
	inline const char* getTitle() const { return m_config.title; }
	inline bool isFullscreen() const { return m_config.fullscreen; }

	inline uint16_t getWindowId() const { return m_id; }

protected:
	void dispatchEvent(Event& event);
protected:
	void* m_native_window;
private:
	WindowConfig m_config;
	EventDispatcher m_event_dispatcher;
	uint16_t m_id;
	static uint16_t s_id_counter;
};
}
