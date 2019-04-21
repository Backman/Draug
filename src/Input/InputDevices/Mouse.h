#pragma once

#include "Draug.h"
#include "Input/InputTypes.h"

namespace Draug {
namespace Input {
class Mouse {
public:
	inline bool isButtonDown(MouseButton::Code button) const { return m_down[button]; }
	inline bool isButtonUp(MouseButton::Code button) const { return m_up[button]; }
	inline bool isButtonPressed(MouseButton::Code button) const { return m_pressed[button]; }
	inline bool isAnyButtonDown() const { return m_down.any(); }
	inline bool isAnyButtonUp() const { return m_up.any(); }
	inline bool isAnyButtonPressed() const { return m_pressed.any(); }

	inline void onButtonDown(const MouseEvent& event) {
		m_down[event.button] = true;
		m_pressed[event.button] = true;
	}

	inline void onButtonUp(const MouseEvent& event) {
		m_up[event.button] = true;
		m_pressed[event.button] = false;
	}

	inline void onMove(const MouseEvent& event) {
	}

	inline void onScroll(const MouseEvent& event) {
	}

	inline void reset() {
		m_down.reset();
		m_up.reset();
	}
private:
	std::bitset<MouseButton::Count> m_down;
	std::bitset<MouseButton::Count> m_up;
	std::bitset<MouseButton::Count> m_pressed;
};
}
}
