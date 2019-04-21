#pragma once

#include "Core/Types.h"
#include "Core/Event/Event.h"
#include <SDL/SDL_scancode.h>

namespace Draug {
namespace Input {

struct MouseButton {
	enum Code : uint8 {
		Left = 0,
		Right,
		Middle,
		LeftOne,
		LeftTwo,

		Count,
		Invalid = 0xFF,
	};
};

struct Key {
	enum Code {
		Space = 0,
		Apostrophe,
		Comma,
		Minus,
		Period,
		Slash,
		N0,
		N1,
		N2,
		N3,
		N4,
		N5,
		N6,
		N7,
		N8,
		N9,
		Semicolon,
		Equal,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		LeftBracket,
		BackSlash,
		RightBracket,
		GraveAccent,
		World1,
		World2,
		Escape,
		Enter,
		Tab,
		BackSpace,
		Insert,
		Delete,
		Right,
		Left,
		Down,
		Up,
		PageUp,
		PageDown,
		Home,
		End,
		CapsLock,
		ScrollLock,
		NumLock,
		PrintScreen,
		Pause,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		F16,
		F17,
		F18,
		F19,
		F20,
		F21,
		F22,
		F23,
		F24,
		F25,
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		NumDecimal,
		NumDivide,
		NumMultiply,
		NumSubtract,
		NumAdd,
		NumEnter,
		NumEqual,
		LeftShift,
		LeftControl,
		LeftAlt,
		LeftSuper,
		RightShift,
		RightControl,
		RightAlt,
		RightSuper,
		Menu,

		Count,
		Invalid = 0xFFFFFFFF,
	};
};

struct KeyEvent : public Event {
	enum Type {
		Down = 0,
		Up,
		Repeat,

		Count,
		Invalid = 0xFFFFFFFF,
	};
	KeyEvent() {}
	KeyEvent(Type type, SDL_Scancode key) :
		type(type), key(key) {
	}
	Type type = Type::Invalid;

	//Key::Code key = Key::Invalid;
	SDL_Scancode key = SDL_SCANCODE_UNKNOWN;

	DRAUG_EVENT_CLASS(EventType::Key)
};

struct MouseEvent : public Event {
	enum Type {
		Down = 0,
		Up,
		Move,
		Scroll,

		Count,
		Invalid = 0xFFFFFFFF,
	};

	Type type = Type::Invalid;

	MouseButton::Code button = MouseButton::Invalid;

	int32 x_scroll;
	int32 y_scroll;

	int32 x_pos;
	int32 y_pos;

	int32 x_move;
	int32 y_move;

	inline static MouseEvent createButtonEvent(Type type, MouseButton::Code button, int32 x_pos, int32 y_pos) {
		MouseEvent e;
		e.type = type;
		e.button = button;
		e.x_pos = x_pos;
		e.y_pos = y_pos;

		return e;
	}

	inline static MouseEvent createMoveEvent(int32 x_move, int32 y_move, int32 x_pos, int32 y_pos) {
		MouseEvent e;
		e.type = Type::Move;
		e.x_move = x_move;
		e.y_move = y_move;
		e.x_pos = x_pos;
		e.y_pos = y_pos;
		return e;
	}

	inline static MouseEvent createScrollEvent(int32 x_scroll, int32 y_scroll) {
		MouseEvent e;
		e.type = Type::Scroll;
		x_scroll = x_scroll;
		y_scroll = y_scroll;
		return e;
	}

	DRAUG_EVENT_CLASS(EventType::Mouse)
};

}
}

