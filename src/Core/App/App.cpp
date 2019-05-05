#include "App.h"
#include "Renderer/Renderer.h"
#include "Core/Window/Window.h"
#include "Core/Window/WindowConfig.h"
#include "Input/Input.h"

namespace Draug {

App* App::s_instance = nullptr;


App::~App() {
}

void App::run() {
	initialize();
	while (m_state_machine.isRunning()) {
		float tick = m_timer.tick();
		float unscaled_dt = tick;
		float dt = tick * m_time_scale;

		m_time += dt;
		m_unscaled_time += unscaled_dt;

		m_renderer->beginFrame();

		m_state_machine.fixedTick();
		m_state_machine.tick(dt);
		m_world.fixedTick();
		m_world.tick(dt);
		Input::Input::reset();

		m_renderer->renderFrame();
		m_renderer->endFrame();
	}
	shutdown();
}

void App::onEvent(Event& event) {
	Event::dispatch<WindowCloseEvent>(event, BIND_FN(App, onWindowClose));
	m_state_machine.onEvent(event);
}

void App::initialize() {
	s_instance = this;
	WindowConfig window_config = WindowConfig::createWindowed("Draug", 0, 0, 1024, 720);
	m_window = Window::createWindow(window_config);
	m_renderer = new Renderer();
	m_renderer->init(m_window);

	Input::Input::init(m_window);

	m_window->subscribeEvent(BIND_FN(App, onEvent));
	m_world.initialize(this);
	m_timer.reset();
	onInitialize();
}

void App::shutdown() {
	onShutdown();

	m_world.shutdown();
	m_state_machine.transition(StateTransition::quit());
	m_renderer->shutdown();
	m_window->shutdown();

	delete m_renderer;
	delete m_window;
}

bool App::onWindowClose(const WindowCloseEvent& event) {
	m_state_machine.transition(StateTransition::quit());
	return true;
}

}