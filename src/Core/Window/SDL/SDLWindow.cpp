#include "SDLWindow.h"
#include "Log/Log.h"
#include "Core/Window/WindowConfig.h"
#include "Input/InputTypes.h"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

namespace Draug {

Window* Window::createWindow(const WindowConfig& config) {
	SDLWindow* window = new SDLWindow();
	if (window->initialize(config) == false) {
		delete window;
		return nullptr;
	}
	return window;
}

bool SDLWindow::initialize(const WindowConfig& config) {
	if (m_window != nullptr) {
		DRAUG_CORE_ERROR("Window has already been initialized");
		return false;
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		DRAUG_CORE_ERROR("Failed to initialize SDL window: {0}", SDL_GetError());
		return false;
	}

	uint32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
	if (config.fullscreen) {
		window_flags |= SDL_WINDOW_FULLSCREEN;
	}

	uint32 pos_x = config.pos_x == 0 ? SDL_WINDOWPOS_UNDEFINED : config.pos_x;
	uint32 pos_y = config.pos_y == 0 ? SDL_WINDOWPOS_UNDEFINED : config.pos_y;

	m_window = SDL_CreateWindow(config.title, pos_x, pos_y, config.width, config.height, window_flags);
	if (m_window == nullptr) {
		DRAUG_CORE_ERROR("Failed to create SDL window: {0}", SDL_GetError());
		return false;
	}

	return true;
}

void SDLWindow::shutdown() {
	SDL_DestroyWindow(m_window);
	SDL_Quit();
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
				Input::KeyEvent event;
				event.key = sdl_event.key.keysym.scancode;
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
				Input::KeyEvent event(Input::KeyEvent::Up, sdl_event.key.keysym.scancode);
				dispatchEvent(event);
			}
			break;
			case SDL_MOUSEMOTION:
			{
				SDL_MouseMotionEvent motion = sdl_event.motion;
				dispatchEvent(Input::MouseEvent::createMoveEvent(motion.xrel, motion.yrel, motion.x, motion.y));
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				SDL_MouseButtonEvent mouse = sdl_event.button;
				dispatchEvent(Input::MouseEvent::createButtonEvent(Input::MouseEvent::Down, Input::MouseButton::Code(mouse.button), mouse.x, mouse.y));
			}
			break;
			case SDL_MOUSEBUTTONUP:
			{
				SDL_MouseButtonEvent mouse = sdl_event.button;
				dispatchEvent(Input::MouseEvent::createButtonEvent(Input::MouseEvent::Up, Input::MouseButton::Code(mouse.button), mouse.x, mouse.y));
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
