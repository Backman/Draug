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

	virtual void begin_frame() = 0;
	virtual void render() = 0;
	virtual void end_frame() = 0;

	EventCallbackId subscribe_event(EventCallback callback);
	void unsubscribe_event(EventCallbackId id);
	inline EventDispatcher* get_event_dispatcher() { return &m_event_dispatcher; }

	inline void* get_native_window_ptr() { return m_native_window; }

	inline int get_width() const { return m_config.width; }
	inline int get_height() const { return m_config.height; }
	inline const char* get_title() const { return m_config.title; }
	inline bool is_fullscreen() const { return m_config.fullscreen; }

	inline uint16_t get_window_id() const { return m_id; }

	void dispatch_event(Event& event);
protected:
	void* m_native_window;
private:
	WindowConfig m_config;
	EventDispatcher m_event_dispatcher;
	uint16_t m_id;
	static uint16_t s_id_counter;
};
}
