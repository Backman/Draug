#ifdef DRAUG_GLFW
#include "glfwWindow.h"
#include "Log/Log.h"
#include "Core/Event/Event.h"
#include "Input/InputTypes.h"

#include <GLFW/glfw3.h>
#ifdef DRAUG_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3native.h>

namespace Draug {

Window* Window::create_window(const WindowConfig& config) {
	glfwWindow* window = new glfwWindow();
	if (window->init(config) == false) {
		DRAUG_LOG_CORE_ERROR("Failed to init window");
		delete window;
		return nullptr;
	}
	return window;
}

static Input::Key::Code s_key_table[GLFW_KEY_LAST + 1];
static void initKeyTable() {
	for (size_t i = 0; i <= GLFW_KEY_LAST; i++) {
		s_key_table[i] = Input::Key::Code::Invalid;
	}
	s_key_table[GLFW_KEY_SPACE] = Input::Key::Code::Space;
	s_key_table[GLFW_KEY_APOSTROPHE] = Input::Key::Code::Apostrophe;
	s_key_table[GLFW_KEY_COMMA] = Input::Key::Code::Comma;
	s_key_table[GLFW_KEY_MINUS] = Input::Key::Code::Minus;
	s_key_table[GLFW_KEY_PERIOD] = Input::Key::Code::Period;
	s_key_table[GLFW_KEY_SLASH] = Input::Key::Code::Slash;
	s_key_table[GLFW_KEY_0] = Input::Key::Code::N0;
	s_key_table[GLFW_KEY_1] = Input::Key::Code::N1;
	s_key_table[GLFW_KEY_2] = Input::Key::Code::N2;
	s_key_table[GLFW_KEY_3] = Input::Key::Code::N3;
	s_key_table[GLFW_KEY_4] = Input::Key::Code::N4;
	s_key_table[GLFW_KEY_5] = Input::Key::Code::N5;
	s_key_table[GLFW_KEY_6] = Input::Key::Code::N6;
	s_key_table[GLFW_KEY_7] = Input::Key::Code::N7;
	s_key_table[GLFW_KEY_8] = Input::Key::Code::N8;
	s_key_table[GLFW_KEY_9] = Input::Key::Code::N9;
	s_key_table[GLFW_KEY_SEMICOLON] = Input::Key::Code::Semicolon;
	s_key_table[GLFW_KEY_EQUAL] = Input::Key::Code::Equal;
	s_key_table[GLFW_KEY_A] = Input::Key::Code::A;
	s_key_table[GLFW_KEY_B] = Input::Key::Code::B;
	s_key_table[GLFW_KEY_C] = Input::Key::Code::C;
	s_key_table[GLFW_KEY_D] = Input::Key::Code::D;
	s_key_table[GLFW_KEY_E] = Input::Key::Code::E;
	s_key_table[GLFW_KEY_F] = Input::Key::Code::F;
	s_key_table[GLFW_KEY_G] = Input::Key::Code::G;
	s_key_table[GLFW_KEY_H] = Input::Key::Code::H;
	s_key_table[GLFW_KEY_I] = Input::Key::Code::I;
	s_key_table[GLFW_KEY_J] = Input::Key::Code::J;
	s_key_table[GLFW_KEY_K] = Input::Key::Code::K;
	s_key_table[GLFW_KEY_L] = Input::Key::Code::L;
	s_key_table[GLFW_KEY_M] = Input::Key::Code::M;
	s_key_table[GLFW_KEY_N] = Input::Key::Code::N;
	s_key_table[GLFW_KEY_O] = Input::Key::Code::O;
	s_key_table[GLFW_KEY_P] = Input::Key::Code::P;
	s_key_table[GLFW_KEY_Q] = Input::Key::Code::Q;
	s_key_table[GLFW_KEY_R] = Input::Key::Code::R;
	s_key_table[GLFW_KEY_S] = Input::Key::Code::S;
	s_key_table[GLFW_KEY_T] = Input::Key::Code::T;
	s_key_table[GLFW_KEY_U] = Input::Key::Code::U;
	s_key_table[GLFW_KEY_V] = Input::Key::Code::V;
	s_key_table[GLFW_KEY_W] = Input::Key::Code::W;
	s_key_table[GLFW_KEY_X] = Input::Key::Code::X;
	s_key_table[GLFW_KEY_Y] = Input::Key::Code::Y;
	s_key_table[GLFW_KEY_Z] = Input::Key::Code::Z;
	s_key_table[GLFW_KEY_LEFT_BRACKET] = Input::Key::Code::LeftBracket;
	s_key_table[GLFW_KEY_BACKSLASH] = Input::Key::Code::BackSlash;
	s_key_table[GLFW_KEY_RIGHT_BRACKET] = Input::Key::Code::RightBracket;
	s_key_table[GLFW_KEY_GRAVE_ACCENT] = Input::Key::Code::GraveAccent;
	s_key_table[GLFW_KEY_WORLD_1] = Input::Key::Code::World1;
	s_key_table[GLFW_KEY_WORLD_2] = Input::Key::Code::World2;
	s_key_table[GLFW_KEY_ESCAPE] = Input::Key::Code::Escape;
	s_key_table[GLFW_KEY_ENTER] = Input::Key::Code::Enter;
	s_key_table[GLFW_KEY_TAB] = Input::Key::Code::Tab;
	s_key_table[GLFW_KEY_BACKSPACE] = Input::Key::Code::BackSpace;
	s_key_table[GLFW_KEY_INSERT] = Input::Key::Code::Insert;
	s_key_table[GLFW_KEY_DELETE] = Input::Key::Code::Delete;
	s_key_table[GLFW_KEY_RIGHT] = Input::Key::Code::Right;
	s_key_table[GLFW_KEY_LEFT] = Input::Key::Code::Left;
	s_key_table[GLFW_KEY_DOWN] = Input::Key::Code::Down;
	s_key_table[GLFW_KEY_UP] = Input::Key::Code::Up;
	s_key_table[GLFW_KEY_PAGE_UP] = Input::Key::Code::PageUp;
	s_key_table[GLFW_KEY_PAGE_DOWN] = Input::Key::Code::PageDown;
	s_key_table[GLFW_KEY_HOME] = Input::Key::Code::Home;
	s_key_table[GLFW_KEY_END] = Input::Key::Code::End;
	s_key_table[GLFW_KEY_CAPS_LOCK] = Input::Key::Code::CapsLock;
	s_key_table[GLFW_KEY_SCROLL_LOCK] = Input::Key::Code::ScrollLock;
	s_key_table[GLFW_KEY_NUM_LOCK] = Input::Key::Code::NumLock;
	s_key_table[GLFW_KEY_PRINT_SCREEN] = Input::Key::Code::PrintScreen;
	s_key_table[GLFW_KEY_PAUSE] = Input::Key::Code::Pause;
	s_key_table[GLFW_KEY_F1] = Input::Key::Code::F1;
	s_key_table[GLFW_KEY_F2] = Input::Key::Code::F2;
	s_key_table[GLFW_KEY_F3] = Input::Key::Code::F3;
	s_key_table[GLFW_KEY_F4] = Input::Key::Code::F4;
	s_key_table[GLFW_KEY_F5] = Input::Key::Code::F5;
	s_key_table[GLFW_KEY_F6] = Input::Key::Code::F6;
	s_key_table[GLFW_KEY_F7] = Input::Key::Code::F7;
	s_key_table[GLFW_KEY_F8] = Input::Key::Code::F8;
	s_key_table[GLFW_KEY_F9] = Input::Key::Code::F9;
	s_key_table[GLFW_KEY_F10] = Input::Key::Code::F10;
	s_key_table[GLFW_KEY_F11] = Input::Key::Code::F11;
	s_key_table[GLFW_KEY_F12] = Input::Key::Code::F12;
	s_key_table[GLFW_KEY_F13] = Input::Key::Code::F13;
	s_key_table[GLFW_KEY_F14] = Input::Key::Code::F14;
	s_key_table[GLFW_KEY_F15] = Input::Key::Code::F15;
	s_key_table[GLFW_KEY_F16] = Input::Key::Code::F16;
	s_key_table[GLFW_KEY_F17] = Input::Key::Code::F17;
	s_key_table[GLFW_KEY_F18] = Input::Key::Code::F18;
	s_key_table[GLFW_KEY_F19] = Input::Key::Code::F19;
	s_key_table[GLFW_KEY_F20] = Input::Key::Code::F20;
	s_key_table[GLFW_KEY_F21] = Input::Key::Code::F21;
	s_key_table[GLFW_KEY_F22] = Input::Key::Code::F22;
	s_key_table[GLFW_KEY_F23] = Input::Key::Code::F23;
	s_key_table[GLFW_KEY_F24] = Input::Key::Code::F24;
	s_key_table[GLFW_KEY_F25] = Input::Key::Code::F25;
	s_key_table[GLFW_KEY_KP_0] = Input::Key::Code::Num0;
	s_key_table[GLFW_KEY_KP_1] = Input::Key::Code::Num1;
	s_key_table[GLFW_KEY_KP_2] = Input::Key::Code::Num2;
	s_key_table[GLFW_KEY_KP_3] = Input::Key::Code::Num3;
	s_key_table[GLFW_KEY_KP_4] = Input::Key::Code::Num4;
	s_key_table[GLFW_KEY_KP_5] = Input::Key::Code::Num5;
	s_key_table[GLFW_KEY_KP_6] = Input::Key::Code::Num6;
	s_key_table[GLFW_KEY_KP_7] = Input::Key::Code::Num7;
	s_key_table[GLFW_KEY_KP_8] = Input::Key::Code::Num8;
	s_key_table[GLFW_KEY_KP_9] = Input::Key::Code::Num9;
	s_key_table[GLFW_KEY_KP_DECIMAL] = Input::Key::Code::NumDecimal;
	s_key_table[GLFW_KEY_KP_DIVIDE] = Input::Key::Code::NumDivide;
	s_key_table[GLFW_KEY_KP_MULTIPLY] = Input::Key::Code::NumMultiply;
	s_key_table[GLFW_KEY_KP_SUBTRACT] = Input::Key::Code::NumSubtract;
	s_key_table[GLFW_KEY_KP_ADD] = Input::Key::Code::NumAdd;
	s_key_table[GLFW_KEY_KP_ENTER] = Input::Key::Code::NumEnter;
	s_key_table[GLFW_KEY_KP_EQUAL] = Input::Key::Code::NumEqual;
	s_key_table[GLFW_KEY_LEFT_SHIFT] = Input::Key::Code::LeftShift;
	s_key_table[GLFW_KEY_LEFT_CONTROL] = Input::Key::Code::LeftControl;
	s_key_table[GLFW_KEY_LEFT_ALT] = Input::Key::Code::LeftAlt;
	s_key_table[GLFW_KEY_LEFT_SUPER] = Input::Key::Code::LeftSuper;
	s_key_table[GLFW_KEY_RIGHT_SHIFT] = Input::Key::Code::RightShift;
	s_key_table[GLFW_KEY_RIGHT_CONTROL] = Input::Key::Code::RightControl;
	s_key_table[GLFW_KEY_RIGHT_ALT] = Input::Key::Code::RightAlt;
	s_key_table[GLFW_KEY_RIGHT_SUPER] = Input::Key::Code::RightSuper;
	s_key_table[GLFW_KEY_MENU] = Input::Key::Code::Menu;
}

static void glfw_errorCallback(int error, const char* description) {
	DRAUG_LOG_CORE_ERROR("GLFW error ({0}): {1}", error, description);
}

static glfwWindow* getWindow(GLFWwindow* window) {
	return (glfwWindow*)glfwGetWindowUserPointer(window);
}

void glfwWindow::glfw_windowCloseCallback(GLFWwindow* window) {
	getWindow(window)->dispatch_event(WindowCloseEvent());
}

void glfwWindow::glfw_windowSizeCallback(GLFWwindow* window, int width, int height) {
	glfwWindow* app_window = getWindow(window);
	WindowResizeEvent event;
	event.width = width;
	event.height = height;
	app_window->dispatch_event(event);
}

void glfwWindow::glfw_windowPosCallback(GLFWwindow* window, int x_pos, int y_pos) {
	glfwWindow* app_window = getWindow(window);
	WindowMovedEvent event;
	event.x_pos = x_pos;
	event.y_pos = y_pos;
	app_window->dispatch_event(event);
}

void glfwWindow::glfw_keyCallback(GLFWwindow* window, int glfw_key, int scancode, int action, int mods) {
	if (glfw_key < 0 || glfw_key > GLFW_KEY_LAST) {
		return;
	}
	Input::KeyEvent event;
	event.key = s_key_table[glfw_key];
	switch (action) {
		case GLFW_PRESS:
		{
			event.type = Input::KeyEvent::Down;
		}
		break;
		case GLFW_RELEASE:
		{
			event.type = Input::KeyEvent::Up;
		}
		break;
		default:
		{
			event.type = Input::KeyEvent::Repeat;
		}
		break;
	}
	getWindow(window)->dispatch_event(event);
}

void glfwWindow::glfw_mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	Input::MouseEvent::Type type;
	switch (action) {
		case GLFW_PRESS:
		{
			type = Input::MouseEvent::Type::Down;
		}
		break;
		case GLFW_RELEASE:
		{
			type = Input::MouseEvent::Type::Up;
		}
		break;
		default:
			return;
	};
	getWindow(window)->dispatch_event(Input::MouseEvent::button_event(type, Input::MouseButton::Code(button)));
}

void glfwWindow::glfw_cursorPosCallbac(GLFWwindow* window, double x, double y) {
	getWindow(window)->dispatch_event(Input::MouseEvent::move_event(x, y));
}

void glfwWindow::glfw_scrollCallback(GLFWwindow* window, double x_scroll, double y_scroll) {
	getWindow(window)->dispatch_event(Input::MouseEvent::scroll_event(x_scroll, y_scroll));
}

bool glfwWindow::init(const WindowConfig& config) {
	if (m_window != nullptr) {
		DRAUG_LOG_CORE_ERROR("Window has already been initialized");
		return false;
	}

	glfwSetErrorCallback(glfw_errorCallback);
	if (glfwInit() == false) {
		DRAUG_LOG_CORE_ERROR("Failed to initialzie GLFW");
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_window = glfwCreateWindow(config.width, config.height, config.title, nullptr, nullptr);
	if (m_window == false) {
		DRAUG_LOG_CORE_ERROR("Failed to create GLFW window");
		return false;
	}

	initKeyTable();

	glfwSetWindowUserPointer(m_window, this);
	glfwSetWindowSizeCallback(m_window, glfw_windowSizeCallback);
	glfwSetWindowCloseCallback(m_window, glfw_windowCloseCallback);
	glfwSetWindowPosCallback(m_window, glfw_windowPosCallback);
	glfwSetKeyCallback(m_window, glfw_keyCallback);
	glfwSetMouseButtonCallback(m_window, glfw_mouseButtonCallback);
	glfwSetCursorPosCallback(m_window, glfw_cursorPosCallbac);
	glfwSetScrollCallback(m_window, glfw_scrollCallback);

	m_native_window = glfwGetWin32Window(m_window);

	return Window::init(config);
}

void glfwWindow::shutdown() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void glfwWindow::begin_frame() {
	glfwPollEvents();

}

void glfwWindow::render() {

}

void glfwWindow::end_frame() {

}

int glfwWindow::get_width() const {
	int width;
	glfwGetWindowSize(m_window, &width, nullptr);
	return width;
}

int glfwWindow::get_height() const {
	int height;
	glfwGetWindowSize(m_window, nullptr, &height);
	return height;
}

int glfwWindow::get_framebuffer_width() const {
	int width;
	glfwGetFramebufferSize(m_window, &width, nullptr);
	return width;
}

int glfwWindow::get_framebuffer_height() const {
	int height;
	glfwGetFramebufferSize(m_window, nullptr, &height);
	return height;
}
}
#endif
