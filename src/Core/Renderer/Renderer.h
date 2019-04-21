#pragma once

#include "Core/Renderer/Texture.h"
#include "Core/Renderer/SDL/SDLRenderer.h"

namespace Draug {
class Window;

struct RendererConfig {
	Window* window;
};

class RendererImpl : public SDLRenderer {
};

class Renderer {
public:
	static void init(const RendererConfig& config);
	static void render();
	static void shutdown();

	static void beginPass();
	static void endPass();
	static void draw(const Texture& texture, const int32 x_pos, const int32 y_pos);

	static Texture* getTexture(const std::string& path, const TextureData& data = TextureData());

private:
	static RendererImpl m_impl;
};
}
