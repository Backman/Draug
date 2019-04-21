#pragma once

#include "Core/Window/Window.h"
#include <SDL/SDL.h>

namespace Draug {
class SDLWindow : public Window {
public:
	bool initialize(const WindowConfig& config) override;
	void shutdown() override;

	void* getNativeWindow() { return m_window; }

protected:
	void pollEvents() override;

private:
	SDL_Window* m_window;
};
}
