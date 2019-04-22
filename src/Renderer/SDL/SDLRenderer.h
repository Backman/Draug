#pragma once 

#include "Core/Types.h"
#include <string>

struct SDL_Renderer;
struct SDL_Window;

namespace Draug {
struct RendererConfig;
class Texture;
struct TextureData;

class SDLRenderer {
public:
	void init(const RendererConfig& config);
	void shutdown();
	void render();

	void beginPass();
	void endPass();
	void draw(const Texture& texture, const int32 x_pos, const int32 y_pos);

	Texture* createTexture(const std::string& path, const TextureData& data);
private:
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;
};
}
