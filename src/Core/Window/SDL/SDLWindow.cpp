#include "SDLWindow.h"
#include "Log/Log.h"
#include "Core/Window/WindowConfig.h"
#include "Input/InputTypes.h"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_syswm.h>

namespace Draug {

static Input::Key::Code s_key_table[SDL_NUM_SCANCODES + 1];
static void initKeyTable() {
	for (size_t i = 0; i <= SDL_NUM_SCANCODES; i++) {
		s_key_table[i] = Input::Key::Code::Invalid;
	}
	s_key_table[SDL_SCANCODE_SPACE] = Input::Key::Code::Space;
	s_key_table[SDL_SCANCODE_APOSTROPHE] = Input::Key::Code::Apostrophe;
	s_key_table[SDL_SCANCODE_COMMA] = Input::Key::Code::Comma;
	s_key_table[SDL_SCANCODE_MINUS] = Input::Key::Code::Minus;
	s_key_table[SDL_SCANCODE_PERIOD] = Input::Key::Code::Period;
	s_key_table[SDL_SCANCODE_SLASH] = Input::Key::Code::Slash;
	s_key_table[SDL_SCANCODE_0] = Input::Key::Code::N0;
	s_key_table[SDL_SCANCODE_1] = Input::Key::Code::N1;
	s_key_table[SDL_SCANCODE_2] = Input::Key::Code::N2;
	s_key_table[SDL_SCANCODE_3] = Input::Key::Code::N3;
	s_key_table[SDL_SCANCODE_4] = Input::Key::Code::N4;
	s_key_table[SDL_SCANCODE_5] = Input::Key::Code::N5;
	s_key_table[SDL_SCANCODE_6] = Input::Key::Code::N6;
	s_key_table[SDL_SCANCODE_7] = Input::Key::Code::N7;
	s_key_table[SDL_SCANCODE_8] = Input::Key::Code::N8;
	s_key_table[SDL_SCANCODE_9] = Input::Key::Code::N9;
	s_key_table[SDL_SCANCODE_SEMICOLON] = Input::Key::Code::Semicolon;
	s_key_table[SDL_SCANCODE_A] = Input::Key::Code::Equal;
	s_key_table[SDL_SCANCODE_B] = Input::Key::Code::A;
	s_key_table[SDL_SCANCODE_C] = Input::Key::Code::B;
	s_key_table[SDL_SCANCODE_C] = Input::Key::Code::C;
	s_key_table[SDL_SCANCODE_D] = Input::Key::Code::D;
	s_key_table[SDL_SCANCODE_E] = Input::Key::Code::E;
	s_key_table[SDL_SCANCODE_F] = Input::Key::Code::F;
	s_key_table[SDL_SCANCODE_G] = Input::Key::Code::G;
	s_key_table[SDL_SCANCODE_H] = Input::Key::Code::H;
	s_key_table[SDL_SCANCODE_I] = Input::Key::Code::I;
	s_key_table[SDL_SCANCODE_J] = Input::Key::Code::J;
	s_key_table[SDL_SCANCODE_K] = Input::Key::Code::K;
	s_key_table[SDL_SCANCODE_L] = Input::Key::Code::L;
	s_key_table[SDL_SCANCODE_M] = Input::Key::Code::M;
	s_key_table[SDL_SCANCODE_N] = Input::Key::Code::N;
	s_key_table[SDL_SCANCODE_O] = Input::Key::Code::O;
	s_key_table[SDL_SCANCODE_P] = Input::Key::Code::P;
	s_key_table[SDL_SCANCODE_Q] = Input::Key::Code::Q;
	s_key_table[SDL_SCANCODE_R] = Input::Key::Code::R;
	s_key_table[SDL_SCANCODE_S] = Input::Key::Code::S;
	s_key_table[SDL_SCANCODE_T] = Input::Key::Code::T;
	s_key_table[SDL_SCANCODE_U] = Input::Key::Code::U;
	s_key_table[SDL_SCANCODE_V] = Input::Key::Code::V;
	s_key_table[SDL_SCANCODE_W] = Input::Key::Code::W;
	s_key_table[SDL_SCANCODE_X] = Input::Key::Code::X;
	s_key_table[SDL_SCANCODE_Y] = Input::Key::Code::Y;
	s_key_table[SDL_SCANCODE_Z] = Input::Key::Code::Z;
	s_key_table[SDL_SCANCODE_LEFTBRACKET] = Input::Key::Code::LeftBracket;
	s_key_table[SDL_SCANCODE_BACKSLASH] = Input::Key::Code::BackSlash;
	s_key_table[SDL_SCANCODE_RIGHTBRACKET] = Input::Key::Code::RightBracket;
	s_key_table[SDL_SCANCODE_GRAVE] = Input::Key::Code::GraveAccent;
	s_key_table[SDL_SCANCODE_INTERNATIONAL1] = Input::Key::Code::World1;
	s_key_table[SDL_SCANCODE_INTERNATIONAL2] = Input::Key::Code::World2;
	s_key_table[SDL_SCANCODE_ESCAPE] = Input::Key::Code::Escape;
	s_key_table[SDL_SCANCODE_RETURN] = Input::Key::Code::Enter;
	s_key_table[SDL_SCANCODE_TAB] = Input::Key::Code::Tab;
	s_key_table[SDL_SCANCODE_BACKSPACE] = Input::Key::Code::BackSpace;
	s_key_table[SDL_SCANCODE_INSERT] = Input::Key::Code::Insert;
	s_key_table[SDL_SCANCODE_DELETE] = Input::Key::Code::Delete;
	s_key_table[SDL_SCANCODE_RIGHT] = Input::Key::Code::Right;
	s_key_table[SDL_SCANCODE_LEFT] = Input::Key::Code::Left;
	s_key_table[SDL_SCANCODE_DOWN] = Input::Key::Code::Down;
	s_key_table[SDL_SCANCODE_UP] = Input::Key::Code::Up;
	s_key_table[SDL_SCANCODE_PAGEUP] = Input::Key::Code::PageUp;
	s_key_table[SDL_SCANCODE_PAGEDOWN] = Input::Key::Code::PageDown;
	s_key_table[SDL_SCANCODE_HOME] = Input::Key::Code::Home;
	s_key_table[SDL_SCANCODE_END] = Input::Key::Code::End;
	s_key_table[SDL_SCANCODE_CAPSLOCK] = Input::Key::Code::CapsLock;
	s_key_table[SDL_SCANCODE_SCROLLLOCK] = Input::Key::Code::ScrollLock;
	s_key_table[SDL_SCANCODE_NUMLOCKCLEAR] = Input::Key::Code::NumLock;
	s_key_table[SDL_SCANCODE_PRINTSCREEN] = Input::Key::Code::PrintScreen;
	s_key_table[SDL_SCANCODE_PAUSE] = Input::Key::Code::Pause;
	s_key_table[SDL_SCANCODE_F1] = Input::Key::Code::F1;
	s_key_table[SDL_SCANCODE_F2] = Input::Key::Code::F2;
	s_key_table[SDL_SCANCODE_F3] = Input::Key::Code::F3;
	s_key_table[SDL_SCANCODE_F4] = Input::Key::Code::F4;
	s_key_table[SDL_SCANCODE_F5] = Input::Key::Code::F5;
	s_key_table[SDL_SCANCODE_F6] = Input::Key::Code::F6;
	s_key_table[SDL_SCANCODE_F7] = Input::Key::Code::F7;
	s_key_table[SDL_SCANCODE_F8] = Input::Key::Code::F8;
	s_key_table[SDL_SCANCODE_F9] = Input::Key::Code::F9;
	s_key_table[SDL_SCANCODE_F10] = Input::Key::Code::F10;
	s_key_table[SDL_SCANCODE_F11] = Input::Key::Code::F11;
	s_key_table[SDL_SCANCODE_F12] = Input::Key::Code::F12;
	s_key_table[SDL_SCANCODE_F13] = Input::Key::Code::F13;
	s_key_table[SDL_SCANCODE_F14] = Input::Key::Code::F14;
	s_key_table[SDL_SCANCODE_F15] = Input::Key::Code::F15;
	s_key_table[SDL_SCANCODE_F16] = Input::Key::Code::F16;
	s_key_table[SDL_SCANCODE_F17] = Input::Key::Code::F17;
	s_key_table[SDL_SCANCODE_F18] = Input::Key::Code::F18;
	s_key_table[SDL_SCANCODE_F19] = Input::Key::Code::F19;
	s_key_table[SDL_SCANCODE_F20] = Input::Key::Code::F20;
	s_key_table[SDL_SCANCODE_F21] = Input::Key::Code::F21;
	s_key_table[SDL_SCANCODE_F22] = Input::Key::Code::F22;
	s_key_table[SDL_SCANCODE_F23] = Input::Key::Code::F23;
	s_key_table[SDL_SCANCODE_F24] = Input::Key::Code::F24;
	s_key_table[SDL_SCANCODE_KP_0] = Input::Key::Code::Num0;
	s_key_table[SDL_SCANCODE_KP_1] = Input::Key::Code::Num1;
	s_key_table[SDL_SCANCODE_KP_2] = Input::Key::Code::Num2;
	s_key_table[SDL_SCANCODE_KP_3] = Input::Key::Code::Num3;
	s_key_table[SDL_SCANCODE_KP_4] = Input::Key::Code::Num4;
	s_key_table[SDL_SCANCODE_KP_5] = Input::Key::Code::Num5;
	s_key_table[SDL_SCANCODE_KP_6] = Input::Key::Code::Num6;
	s_key_table[SDL_SCANCODE_KP_7] = Input::Key::Code::Num7;
	s_key_table[SDL_SCANCODE_KP_8] = Input::Key::Code::Num8;
	s_key_table[SDL_SCANCODE_KP_9] = Input::Key::Code::Num9;
	s_key_table[SDL_SCANCODE_KP_DECIMAL] = Input::Key::Code::NumDecimal;
	s_key_table[SDL_SCANCODE_KP_DIVIDE] = Input::Key::Code::NumDivide;
	s_key_table[SDL_SCANCODE_KP_MULTIPLY] = Input::Key::Code::NumMultiply;
	s_key_table[SDL_SCANCODE_KP_MINUS] = Input::Key::Code::NumSubtract;
	s_key_table[SDL_SCANCODE_KP_PLUS] = Input::Key::Code::NumAdd;
	s_key_table[SDL_SCANCODE_KP_ENTER] = Input::Key::Code::NumEnter;
	s_key_table[SDL_SCANCODE_KP_EQUALS] = Input::Key::Code::NumEqual;
	s_key_table[SDL_SCANCODE_LSHIFT] = Input::Key::Code::LeftShift;
	s_key_table[SDL_SCANCODE_LCTRL] = Input::Key::Code::LeftControl;
	s_key_table[SDL_SCANCODE_LALT] = Input::Key::Code::LeftAlt;
	s_key_table[SDL_SCANCODE_LGUI] = Input::Key::Code::LeftSuper;
	s_key_table[SDL_SCANCODE_RSHIFT] = Input::Key::Code::RightShift;
	s_key_table[SDL_SCANCODE_RCTRL] = Input::Key::Code::RightControl;
	s_key_table[SDL_SCANCODE_RALT] = Input::Key::Code::RightAlt;
	s_key_table[SDL_SCANCODE_RGUI] = Input::Key::Code::RightSuper;
	s_key_table[SDL_SCANCODE_MENU] = Input::Key::Code::Menu;
}

#ifdef DRAUG_SDL
Window* Window::createWindow(const WindowConfig& config) {
	SDLWindow* window = new SDLWindow();
	if (window->init(config) == false) {
		delete window;
		return nullptr;
	}
	return window;
}
#endif

bool SDLWindow::init(const WindowConfig& config) {
	if (m_window != nullptr) {
		DRAUG_LOG_CORE_ERROR("Window has already been initialized");
		return false;
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		DRAUG_LOG_CORE_ERROR("Failed to initialize SDL window: {0}", SDL_GetError());
		return false;
	}

	uint32_t window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
	if (config.fullscreen) {
		window_flags |= SDL_WINDOW_FULLSCREEN;
	}

	int x_pos = config.x_pos == 0 ? SDL_WINDOWPOS_UNDEFINED : config.x_pos;
	int y_pos = config.y_pos == 0 ? SDL_WINDOWPOS_UNDEFINED : config.y_pos;

	m_window = SDL_CreateWindow(config.title, x_pos, y_pos, config.width, config.height, window_flags);
	if (m_window == nullptr) {
		DRAUG_LOG_CORE_ERROR("Failed to create SDL window: {0}", SDL_GetError());
		return false;
	}

	SDL_SysWMinfo wmi;
	SDL_VERSION(&wmi.version);
	if (SDL_GetWindowWMInfo(m_window, &wmi) == false) {
		DRAUG_LOG_CORE_ERROR("Failed to get native window: {0}", SDL_GetError());
		return false;
	}
	initKeyTable();

	m_native_window = wmi.info.win.window;
	return Window::init(config);
}

void SDLWindow::shutdown() {
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void SDLWindow::beginFrame() {
	pollEvents();
}

void SDLWindow::render() {
}

void SDLWindow::endFrame() {
}

void SDLWindow::pollEvents() {
	SDL_Event sdl_event;
	while (SDL_PollEvent(&sdl_event)) {
		if (sdl_event.type == SDL_QUIT) {
			WindowCloseEvent event;
			dispatchEvent(event);
			break;
		}
		if (sdl_event.type == SDL_WINDOWEVENT) {
			switch (sdl_event.window.type) {
				case SDL_WINDOWEVENT_MOVED:
				{
					WindowMovedEvent event;
					event.x_pos = sdl_event.window.data1;
					event.y_pos = sdl_event.window.data2;
					dispatchEvent(event);
				}
				break;
				case SDL_WINDOWEVENT_RESIZED:
				{
					WindowResizeEvent event;
					event.height = sdl_event.window.data1;
					event.width = sdl_event.window.data2;
					dispatchEvent(event);
				}
				break;
				case SDL_WINDOWEVENT_CLOSE:
				{
					sdl_event.type = SDL_QUIT;
					SDL_PushEvent(&sdl_event);
				}
				break;
				default:
				{
				}
				break;
			}
		}
		switch (sdl_event.type) {

			case SDL_KEYDOWN:
			{
				SDL_Scancode scancode = sdl_event.key.keysym.scancode;
				if (scancode < 0 || scancode > SDL_NUM_SCANCODES) {
					return;
				}
				Input::KeyEvent event;
				event.key = s_key_table[scancode];
				if (sdl_event.key.repeat != 0) {
					event.type = Input::KeyEvent::Repeat;
				}
				else {
					event.type = Input::KeyEvent::Down;
				}
				dispatchEvent(event);
			}
			break;
			case SDL_KEYUP:
			{
				SDL_Scancode scancode = sdl_event.key.keysym.scancode;
				if (scancode < 0 || scancode > SDL_NUM_SCANCODES) {
					return;
				}
				Input::KeyEvent event;
				event.key = s_key_table[scancode];
				event.type = Input::KeyEvent::Up;
				dispatchEvent(event);
			}
			break;
			case SDL_MOUSEMOTION:
			{
				SDL_MouseMotionEvent motion = sdl_event.motion;
				dispatchEvent(Input::MouseEvent::createMoveEvent(motion.x, motion.y));
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				SDL_MouseButtonEvent mouse = sdl_event.button;
				dispatchEvent(Input::MouseEvent::createButtonEvent(Input::MouseEvent::Down, Input::MouseButton::Code(mouse.button)));
			}
			break;
			case SDL_MOUSEBUTTONUP:
			{
				SDL_MouseButtonEvent mouse = sdl_event.button;
				dispatchEvent(Input::MouseEvent::createButtonEvent(Input::MouseEvent::Up, Input::MouseButton::Code(mouse.button)));
			}
			break;
			case SDL_MOUSEWHEEL:
			{
				SDL_MouseWheelEvent wheel = sdl_event.wheel;
				dispatchEvent(Input::MouseEvent::createScrollEvent(wheel.x, wheel.y));
			}
			break;
			default:
				break;
		}
	}
}
}
