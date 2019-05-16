#pragma once


#include "Draug.h"

namespace Draug {

enum EventType {
	WindowMoved,
	WindowResized,
	WindowClosed,
	Key,
	Mouse,

	Count,
	Invalid = 0xFFFFFFFF,
};
#define DRAUG_EVENT_CLASS(type) static EventType s_get_type() { return type; }\
								virtual EventType get_type() const override { return s_get_type(); }
#define BIND_FN(clazz, fn) std::bind(&clazz::fn, this, std::placeholders::_1)
#define BIND_STATIC_FN(clazz, fn) std::bind(&clazz::fn, std::placeholders::_1)

struct Event {
	template<typename T>
	using DispatchCallback = std::function<bool(const T&)>;

	template<typename T>
	static bool dispatch(const Event& event, DispatchCallback<T> callback) {
		if (event.get_type() == T::s_get_type()) {
			return callback(*(T*)& event);
		}
		return false;
	}

	template<typename T>
	static bool is_of_type(const Event& event) {
		return event.getType() == T::s_getType();
	}

	template<typename T>
	static bool try_cast(Event& event, T* out_event) {
		if (event.get_type() == T::s_get_type()) {
			*out_event = *(T*)&event;
			return true;
		}
		out_event = nullptr;
		return false;
	}


	virtual EventType get_type() const = 0;
private:
};

using EventCallback = std::function<void(Event&)>;
typedef int EventCallbackId;

class EventDispatcher {
public:
	inline EventCallbackId subscribe(EventCallback callback) {
		const EventCallbackId id = ++s_id;
		m_callbacks[id] = callback;
		return id;
	}

	inline void unsubscribe(const EventCallbackId& id) {
		m_callbacks.erase(id);
	}

	void dispatch(Event& event) {
		for (auto& it : m_callbacks) {
			it.second(event);
		}
	}

private:
	static EventCallbackId s_id;
	std::unordered_map<EventCallbackId, EventCallback> m_callbacks;
};

struct WindowMovedEvent : Event {
	int x_pos;
	int y_pos;

	DRAUG_EVENT_CLASS(EventType::WindowMoved)
};

struct WindowResizeEvent : Event {
	int width;
	int height;

	DRAUG_EVENT_CLASS(EventType::WindowResized)
};

struct WindowCloseEvent : Event {
	DRAUG_EVENT_CLASS(EventType::WindowClosed)
};
}