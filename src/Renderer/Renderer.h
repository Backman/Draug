#pragma once

#if DRAUG_SDL_RENDERER
#include "Renderer/SDL/SDLRenderer.h"
namespace Draug {
class RendererImpl : public SDLRenderer {};
}
#elif DRAUG_BGFX_RENDERER
#include "Renderer/bgfx/bgfxRenderer.h"
namespace Draug {
class RendererImpl : public bgfxRenderer {};
}
#endif

#include "Renderer/Texture.h"

namespace Draug {
class Window;

struct RendererConfig {
	Window* window;
};

class Renderer {
public:
	static void init(const RendererConfig& config);
	static void shutdown();

	static void beginPass();
	static void render();
	static void endPass();

	static void draw(const Texture& texture, const int32 x_pos, const int32 y_pos);

	static Texture* getTexture(const std::string& path, const TextureData& data = TextureData());

private:
	static RendererImpl m_impl;
};
}
