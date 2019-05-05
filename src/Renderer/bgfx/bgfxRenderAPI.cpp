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
	// Use debug font to print information about this example.
	bgfx::dbgTextClear();
	bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");
	bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
	bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
	bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
	const bgfx::Stats * stats = bgfx::getStats();
	bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.",
		stats->width, stats->height, stats->textWidth, stats->textHeight);
	// Enable stats or debug text.
}

void bgfxRendererAPI::endFrame() {
	m_window->endFrame();

	// Advance to next frame. Process submitted rendering primitives.
	bgfx::frame();
}
}
