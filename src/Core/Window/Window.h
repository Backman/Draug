#pragma once

#include "Draug.h"
#include "Core/Event/Event.h"
#include "Core/Window/WindowConfig.h"

namespace Draug {
class Window {
public:
	static Window* create_window(const WindowConfig& config);

	Window() = default;
	Window(const Window& other) = delete;
	virtual ~Window() = default;

	inline virtual bool init(const WindowConfig& config) {
		m_id = s_id_counter++;
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

	virtual int get_width() const = 0;
	virtual int get_height() const = 0;
	virtual int get_framebuffer_width() const = 0;
	virtual int get_framebuffer_height() const = 0;
	inline const char* get_title() const { return m_title; }
	inline bool is_fullscreen() const { return m_fullscreen; }

	inline uint16_t get_id() const { return m_id; }

	void dispatch_event(Event& event);
protected:
	void* m_native_window;
	const char* m_title;
	bool m_fullscreen = false;
private:
	EventDispatcher m_event_dispatcher;
	uint16_t m_id;
	static uint16_t s_id_counter;
};
}
