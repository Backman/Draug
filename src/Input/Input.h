#pragma once

#include "Draug.h"
#include "Core/Event/Event.h"
#include "InputTypes.h"
#include "InputDevices/Keyboard.h"
#include "InputDevices/Mouse.h"
#include "Core/Window/Window.h"

namespace Draug {
namespace Input {
class Input {
public:
	using KeyEventCallback = std::function<void(const MouseEvent&)>;
	using MouseEventCallback = std::function<void(const MouseEvent&)>;
	inline static void init(Window* window) {
		s_dispatcher = window->get_event_dispatcher();
		s_dispatcher->subscribe(BIND_STATIC_FN(Input, on_event));
	}

	inline static void reset() {
		keyboard.reset();
		mouse.reset();
	}

private:
	inline static void on_event(const Event& event) {
		Event::dispatch<KeyEvent>(event, BIND_STATIC_FN(Input, on_key_event));
		Event::dispatch<MouseEvent>(event, BIND_STATIC_FN(Input, on_mouse_event));
	}

	inline static bool on_key_event(const KeyEvent& event) {
		switch (event.type) {
			case KeyEvent::Down:
			{
				keyboard.onKeyDown(event);
				break;
			}
			break;
			case KeyEvent::Up:
			{
				keyboard.onKeyUp(event);
				break;
			}
			break;
			case KeyEvent::Repeat:
			{
				keyboard.onKeyRepeat(event);
				break;
			}
			break;
			default:
				break;
		}
		//s_dispatcher->dispatch(event);
		return true;
	}

	inline static bool on_mouse_event(const MouseEvent& event) {
		switch (event.type) {
			case MouseEvent::Down:
			{
				mouse.on_button_down(event);
				break;
			}
			break;
			case MouseEvent::Up:
			{
				mouse.on_button_up(event);
				break;
			}
			break;
			case MouseEvent::Move:
			{
				mouse.on_move(event);
				break;
			}
			break;
			case MouseEvent::Scroll:
			{
				mouse.on_scroll(event);
				break;
			}
			break;
			default:
				break;
		}
		//s_dispatcher->dispatch(event);
		return true;
	}

public:
	static Keyboard keyboard;
	static Mouse mouse;
private:
	static EventDispatcher* s_dispatcher;
};
}
}
