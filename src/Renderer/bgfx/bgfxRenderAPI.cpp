#include "bgfxRenderAPI.h"
#include "Log/Log.h"
#include "Core/Window/Window.h"
#include <bgfx/platform.h>
#include <bgfx/bgfx.h>
#include <bx/bx.h>

namespace Draug {

void bgfxRendererAPI::init(Window* window) {
	m_window = window;
	bgfx::renderFrame();

	bgfx::Init init;
	init.platformData.nwh = m_window->getNativeWindow();
	init.type = bgfx::RendererType::OpenGL;
	init.resolution.width = m_window->getWidth();
	init.resolution.height = m_window->getHeight();
	init.resolution.reset = BGFX_RESET_NONE;
	if (bgfx::init(init) == false) {
		DRAUG_LOG_CORE_ERROR("Failed to init bgfx");
		return;
	}

#ifdef DRAUG_DEBUG
	bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_PROFILER);
#endif
}

void bgfxRendererAPI::shutdown() {
	bgfx::shutdown();
}

void bgfxRendererAPI::beginFrame() {
	bgfx::touch(m_window->getWindowId());
	bgfx::setViewClear(m_window->getWindowId(), BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
	bgfx::setViewRect(m_window->getWindowId(), 0, 0, (uint16_t)m_window->getWidth(), (uint16_t)m_window->getHeight());
	m_window->beginFrame();
}

void bgfxRendererAPI::renderFrame() {
	m_window->render();
}

void bgfxRendererAPI::endFrame() {
	m_window->endFrame();

	// Advance to next frame. Process submitted rendering primitives.
	bgfx::frame();
}
}
