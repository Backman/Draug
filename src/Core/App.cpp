#include "App.h"
#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "Window/WindowConfig.h"
#include "Input/Input.h"

namespace Draug {

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

		Input::Input::reset();
	}
	shutdown();
}

void App::onEvent(const Event& event) {
	Event::dispatch<WindowCloseEvent>(event, BIND_FN(App, onWindowClose));
}

void App::initialize() {
	s_instance = this;
	WindowConfig window_config = WindowConfig::createWindowed("Draug", 0, 0, 1024, 720);
	m_window = Window::createWindow(window_config);
	m_window->subscribeEvent(BIND_FN(App, onEvent));

	Input::Input::init(m_window);

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