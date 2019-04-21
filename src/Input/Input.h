#pragma once

#include "Draug.h"
#include "Core/Event/Event.h"
#include "InputTypes.h"
#include "InputDevice/Keyboard.h"
#include "InputDevice/Mouse.h"
#include "Core/Window/Window.h"

namespace Draug {
namespace Input {
class Input {
public:
	using KeyEventCallback = std::function<void(const MouseEvent&)>;
	using MouseEventCallback = std::function<void(const MouseEvent&)>;
	inline static void init(Window* window) {
		s_dispatcher = window->getEventDispatcher();
		s_dispatcher->subscribe(BIND_STATIC_FN(Input, onEvent));
	}

	inline static void reset() {
		keyboard.reset();
		mouse.reset();
	}

private:
	inline static void onEvent(const Event& event) {
		Event::dispatch<KeyEvent>(event, BIND_STATIC_FN(Input, onKeyEvent));
		Event::dispatch<MouseEvent>(event, BIND_STATIC_FN(Input, onMouseEvent));
	}

	inline static bool onKeyEvent(const KeyEvent& event) {
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

	inline static bool onMouseEvent(const MouseEvent& event) {
		switch (event.type) {
			case MouseEvent::Down:
			{
				mouse.onButtonDown(event);
				break;
			}
			break;
			case MouseEvent::Up:
			{
				mouse.onButtonUp(event);
				break;
			}
			break;
			case MouseEvent::Move:
			{
				mouse.onMove(event);
				break;
			}
			break;
			case MouseEvent::Scroll:
			{
				mouse.onScroll(event);
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
