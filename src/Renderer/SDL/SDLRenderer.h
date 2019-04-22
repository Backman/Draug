#pragma once 

#include "Core/Types.h"
#include <string>

struct SDL_Window;
typedef void* SDL_GLContext;

namespace Draug {
struct RendererConfig;
class Texture;
struct TextureData;

class SDLRenderer {
public:
	void init(const RendererConfig& config);
	void shutdown();

	void beginPass();
	void render();
	void endPass();

	void draw(const Texture& texture, const int32 x_pos, const int32 y_pos);

	Texture* createTexture(const std::string& path, const TextureData& data);
private:
	SDL_GLContext m_context;
	SDL_Window* m_window;
};
}
