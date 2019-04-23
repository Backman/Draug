#pragma once


#include "Draug.h"

namespace Draug {

enum EventType {
	WindowResized,
	WindowClosed,
	Key,
	Mouse,

	Count,
	Invalid = 0xFFFFFFFF,
};
#define DRAUG_EVENT_CLASS(type) static EventType s_getType() { return type; }\
								virtual EventType getType() const override { return s_getType(); }
#define BIND_FN(clazz, fn) std::bind(&clazz::fn, this, std::placeholders::_1)
#define BIND_STATIC_FN(clazz, fn) std::bind(&clazz::fn, std::placeholders::_1)

struct Event {
	template<typename T>
	using DispatchCallback = std::function<bool(const T&)>;

	template<typename T>
	static bool dispatch(const Event& event, DispatchCallback<T> callback) {
		EventType t = event.getType();
		EventType s_t = T::s_getType();
		if (event.getType() == T::s_getType()) {
			return callback(*(T*)& event);
		}
		return false;
	}


	virtual EventType getType() const = 0;
private:
};

using EventCallback = std::function<void(const Event&)>;
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

	void dispatch(const Event& event) {
		for (const auto& it : m_callbacks) {
			it.second(event);
		}
	}

private:
	static EventCallbackId s_id;
	std::unordered_map<EventCallbackId, EventCallback> m_callbacks;
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