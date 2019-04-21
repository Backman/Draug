#include "SDLWindow.h"
#include "Core/Log.h"
#include "Core/Window/WindowConfig.h"
#include <SDL/SDL.h>

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

	uint32 window_flags = SDL_WINDOW_SHOWN;
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
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			WindowCloseEvent evt;
			onEvent(evt);
			break;
		}
		if (event.type == SDL_WINDOWEVENT) {
			switch (event.window.type) {
				case SDL_WINDOWEVENT_RESIZED:
				{
					WindowResizeEvent evt;
					evt.height = event.window.data1;
					evt.width = event.window.data2;
					onEvent(evt);
				}
				break;
				case SDL_WINDOWEVENT_CLOSE:
				{
					event.type = SDL_QUIT;
					SDL_PushEvent(&event);
				}
				break;
				default:
				{
				}
				break;
			}
		}
		switch (event.type) {

			case SDL_KEYDOWN:
			{
			}
			break;
			case SDL_KEYUP:
			{
			}
			break;
			case SDL_MOUSEMOTION:
			{
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
			}
			break;
			case SDL_MOUSEBUTTONUP:
			{
			}
			break;
			case SDL_MOUSEWHEEL:
			{
			}
			break;
			default:
				break;
		}
	}
}
}
