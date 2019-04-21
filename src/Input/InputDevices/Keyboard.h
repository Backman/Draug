#pragma once

#include "Draug.h"
#include "Input/InputTypes.h"

namespace Draug {
namespace Input {
class Keyboard {
public:
	//inline bool isKeyDown(Key::Code key) const { return m_down[key]; }
	//inline bool isKeyUp(Key::Code key) const { return m_up[key]; }
	//inline bool isKeyPressed(Key::Code key) const { return m_pressed[key]; }
	//inline bool isKeyRepeated(Key::Code key) const { return m_repeated[key]; }
	inline bool isKeyDown(SDL_Scancode key) const { return m_down[key]; }
	inline bool isKeyUp(SDL_Scancode key) const { return m_up[key]; }
	inline bool isKeyPressed(SDL_Scancode key) const { return m_pressed[key]; }
	inline bool isKeyRepeated(SDL_Scancode key) const { return m_repeated[key]; }
	inline bool isAnyKeyDown() const { return m_down.any();	}
	inline bool isAnyKeyUp() const { return m_up.any();	}
	inline bool isAnyKeyPressed() const { return m_pressed.any();	}
	inline bool isAnyKeyRepeated() const { return m_repeated.any();	}

	inline void onKeyDown(const KeyEvent& event) {
		m_down[event.key] = true;
		m_pressed[event.key] = true;
	}

	inline void onKeyUp(const KeyEvent& event) {
		m_up[event.key] = true;
		m_pressed[event.key] = false;
	}

	inline void onKeyRepeat(const KeyEvent& event) {
		m_repeated[event.key] = true;
	}

	inline void reset() {
		m_down.reset();
		m_up.reset();
		m_repeated.reset();
	}
private:
	std::bitset<SDL_Scancode::SDL_NUM_SCANCODES> m_down;
	std::bitset<SDL_Scancode::SDL_NUM_SCANCODES> m_up;
	std::bitset<SDL_Scancode::SDL_NUM_SCANCODES> m_pressed;
	std::bitset<SDL_Scancode::SDL_NUM_SCANCODES> m_repeated;
};
}
}
