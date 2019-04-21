#include "App.h"
#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "Window/WindowConfig.h"

namespace Draug {
#define BIND_FN(fn) std::bind(&App::fn, this, std::placeholders::_1)

App* App::s_instance = nullptr;


App::~App() {
}

void App::run() {
	initialize();
	m_running = true;
	while (m_running) {
		m_window->update();
		Renderer::render();
		onUpdate();
	}
	shutdown();
}

void App::onEvent(const Event& event) {
	Event::dispatch<WindowCloseEvent>(event, BIND_FN(onWindowClose));
}

void App::initialize() {
	s_instance = this;
	WindowConfig window_config = WindowConfig::createWindowed("Draug", 0, 0, 1024, 720);
	m_window = Window::createWindow(window_config);
	m_window->registerEventHandler(BIND_FN(onEvent));

	RendererConfig renderer_config;
	renderer_config.window = m_window;
	Renderer::init(renderer_config);

	onInitialize();
}

void App::shutdown() {
	if (m_window != nullptr) {
		m_window->shutdown();
		delete m_window;
		m_window = nullptr;
	}
	Renderer::shutdown();
	onShutdown();
}

bool App::onWindowClose(const WindowCloseEvent& event) {
	m_running = false;
	return true;
}

}