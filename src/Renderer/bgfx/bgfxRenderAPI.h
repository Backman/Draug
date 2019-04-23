#pragma once

#include "Draug.h"
#include "Renderer/BaseRenderAPI.h"
#include <bgfx/bgfx.h>
#include <bx/allocator.h>
#include <bx/file.h>

struct SDL_Window;

namespace Draug {
struct RendererConfig;
class Texture;
class Window;
struct TextureData;

class bgfxRendererAPI : public BaseRenderAPI {
public:
	bgfxRendererAPI() = default;
	~bgfxRendererAPI() override = default;
	virtual void init(Window* window) override;
	void shutdown();

	void beginFrame() override;
	void renderFrame() override;
	void endFrame() override;

	inline bx::AllocatorI& getAllocator() { return m_allocator; }
	inline bx::FileReaderI& getFileReader() { return m_file_reader; }
	inline bx::FileWriterI& getFileWriter() { return m_file_writer; }

protected:
	bx::DefaultAllocator m_allocator;
	bx::FileReader m_file_reader;
	bx::FileWriter m_file_writer;

private:
	Window* m_window;
};
}
