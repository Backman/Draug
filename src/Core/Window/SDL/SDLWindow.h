#pragma once

#include "Core/Window/Window.h"
#include <SDL/SDL.h>

namespace Draug {
class SDLWindow : public Window {
public:
	bool init(const WindowConfig& config) override;
	void shutdown() override;

	void beginFrame() override;
	void render() override;
	void endFrame() override;
private:
	void pollEvents();
	SDL_Window* m_window;
};
}
