#pragma once

#include "Draug.h"
#include "Graphics/Renderer/BaseRenderAPI.h"
#include <bgfx/bgfx.h>
#include <bx/allocator.h>
#include <bx/file.h>

struct SDL_Window;

namespace Draug {
struct RendererConfig;
class Texture;
class Window;
struct TextureData;

namespace impl {
class bgfxRendererAPI : public BaseRenderAPI {
public:
	bgfxRendererAPI() = default;
	~bgfxRendererAPI() override = default;
	virtual void init(Window* window) override;
	void shutdown();

	void begin_frame() override;
	void render_frame() override;
	void end_frame() override;

	void reset() override;
private:
	Window* m_window;
};
}
}
