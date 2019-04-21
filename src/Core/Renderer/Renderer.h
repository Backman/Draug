#pragma once

#include "Core/Renderer/SDL/SDLRenderer.h"

namespace Draug {
class Window;
class Texture;
struct TextureData;

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

	static Texture* getTexture(const TextureData& data, const std::string& path);

private:
	static RendererImpl m_impl;
};
}
