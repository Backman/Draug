#pragma once

#include "Draug.h"
#include "Input/InputTypes.h"

namespace Draug {
namespace Input {
class Mouse {
public:
	inline bool is_button_down(MouseButton::Code button) const { return m_down[button]; }
	inline bool is_button_up(MouseButton::Code button) const { return m_up[button]; }
	inline bool is_button_pressed(MouseButton::Code button) const { return m_pressed[button]; }
	inline bool is_any_button_down() const { return m_down.any(); }
	inline bool is_any_button_up() const { return m_up.any(); }
	inline bool is_any_button_pressed() const { return m_pressed.any(); }

	inline void on_button_down(const MouseEvent& event) {
		m_down[event.button] = true;
		m_pressed[event.button] = true;
	}

	inline void on_button_up(const MouseEvent& event) {
		m_up[event.button] = true;
		m_pressed[event.button] = false;
	}

	inline void on_move(const MouseEvent& event) {
	}

	inline void on_scroll(const MouseEvent& event) {
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
