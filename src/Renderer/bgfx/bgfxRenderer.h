#pragma once

#include "Core/Types.h"
#include <bgfx/bgfx.h>

struct SDL_Window;

namespace Draug {
struct RendererConfig;
class Texture;
class Window;
struct TextureData;

class bgfxRenderer {
public:
	void init(const RendererConfig& config);
	void shutdown();

	void beginPass();
	void render();
	void endPass();
	void draw(const Texture& texture, const int32 x_pos, const int32 y_pos);

	Texture* createTexture(const std::string& path, const TextureData& data);
private:

	Window* m_window;
	SDL_Window* m_sdl_window;
	bgfx::ViewId m_view_id;
};
}
