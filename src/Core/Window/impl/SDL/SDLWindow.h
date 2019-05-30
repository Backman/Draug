#pragma once

#include "Core/Window/Window.h"

struct SDL_Window;

namespace Draug {
namespace impl {
class SDLWindow : public Window {
public:
	bool init(const WindowConfig& config) override;
	void shutdown() override;

	void begin_frame() override;
	void render() override;
	void end_frame() override;
private:
	void pollEvents();
	SDL_Window* m_window;
};
}
}
