#pragma once


#include <functional>
#include "Core/Types.h"

namespace Draug {
typedef uint32 EventHandlerId;

enum EventType {
	Unknown,
	WindowResized,
	WindowClosed,

	Count,
};

#define DRAUG_EVENT_CLASS(type) static EventType s_getType() { return type; }\
								virtual EventType getType() const override { return s_getType(); }

struct Event {
	template<typename T>
	using DispatchCallback = std::function<bool(const T&)>;
	inline static EventHandlerId getNextId() {
		return ++s_id;
	};

	template<typename T>
	static bool dispatchEvent(const Event& e, DispatchCallback<T> callback) {
		EventType t = e.getType();
		EventType s_t = T::s_getType();
		if (e.getType() == T::s_getType()) {
			return callback(*(T*)& e);
		}
		return false;
	}


	virtual EventType getType() const = 0;
private:
	static EventHandlerId s_id;
};
typedef std::function<void(const Event&)> EventHandler;

struct WindowResizeEvent : Event {
	uint32 width;
	uint32 height;

	DRAUG_EVENT_CLASS(EventType::WindowResized)
};

struct WindowCloseEvent : Event {
	DRAUG_EVENT_CLASS(EventType::WindowClosed)
};
}