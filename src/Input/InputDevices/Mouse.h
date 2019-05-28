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
		m_x_pos = event.x_pos;
		m_y_pos = event.y_pos;
	}

	inline void on_scroll(const MouseEvent& event) {
		m_x_scroll = event.x_scroll;
		m_y_scroll = event.y_scroll;
	}

	inline void reset() {
		m_down.reset();
		m_up.reset();
		m_x_scroll = m_y_scroll = 0;
	}

	inline float x_pos() { return m_x_pos; }
	inline float y_pos() { return m_y_pos; }
	inline float x_scroll() { return m_x_scroll; }
	inline float y_scroll() { return m_y_scroll; }
private:
	float m_x_pos, m_y_pos;
	float m_x_scroll, m_y_scroll;

	std::bitset<MouseButton::Count> m_down;
	std::bitset<MouseButton::Count> m_up;
	std::bitset<MouseButton::Count> m_pressed;
};
}
}
