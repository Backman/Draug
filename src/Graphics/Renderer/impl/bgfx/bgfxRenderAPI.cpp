#include "bgfxRenderAPI.h"
#include "Log/Log.h"
#include "Core/Window/Window.h"
#include <bgfx/platform.h>
#include <bgfx/bgfx.h>
#include <bx/bx.h>

namespace Draug {
namespace impl {
void bgfxRendererAPI::init(Window* window) {
	m_window = window;
	bgfx::renderFrame();

	bgfx::Init init;
	init.platformData.nwh = m_window->get_native_window_ptr();
	init.type = bgfx::RendererType::OpenGL;
	init.resolution.width = m_window->get_width();
	init.resolution.height = m_window->get_height();
	init.resolution.reset = BGFX_RESET_VSYNC;
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

void bgfxRendererAPI::begin_frame() {
	bgfx::setViewRect(m_window->get_window_id(), 0, 0, (uint16_t)m_window->get_width(), (uint16_t)m_window->get_height());
	bgfx::setViewClear(m_window->get_window_id(), BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
	m_window->begin_frame();
}

void bgfxRendererAPI::renderFrame() {
	m_window->render();
}

void bgfxRendererAPI::end_frame() {
	m_window->end_frame();

	// Advance to next frame. Process submitted rendering primitives.
	bgfx::frame();
}

void bgfxRendererAPI::reset() {
	bgfx::reset(m_window->get_width(), m_window->get_height(), BGFX_RESET_VSYNC);
}
}
}
