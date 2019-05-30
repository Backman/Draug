#include "App.h"
#include "Graphics/Renderer/Renderer.h"
#include "Core/Window/Window.h"
#include "Core/Window/WindowConfig.h"
#include "Input/Input.h"
#include "ImGui/ImGui.h"

namespace Draug {

App* App::s_instance = nullptr;


App::~App() {
}

void App::run() {
	init();
	while (m_state_machine.isRunning()) {
		float tick = m_timer.tick();
		float unscaled_dt = tick;
		float dt = tick * m_time_scale;
		float fixed_dt = 0.16;

		m_time += dt;
		m_unscaled_time += unscaled_dt;

		m_renderer->begin_frame();
		imgui_begin_frame(m_window);

		m_state_machine.fixed_tick(fixed_dt);
		m_state_machine.tick(dt);
		m_world.fixed_tick(fixed_dt);
		m_world.tick(dt);
		imgui_end_frame();

		m_renderer->renderFrame();
		m_renderer->end_frame();

		Input::Input::reset();

	}
	shutdown();
}

void App::on_event(Event& event) {
	Event::dispatch<WindowCloseEvent>(event, BIND_FN(App, on_window_close));
	Event::dispatch<WindowResizeEvent>(event, BIND_FN(App, on_window_resize));
	m_state_machine.on_event(event);
}

void App::init() {
	s_instance = this;
	WindowConfig window_config = WindowConfig::create_windowed("Draug", 1024, 720);
	m_window = Window::create_window(window_config);
	m_renderer = new Renderer();
	m_renderer->init(m_window);

	imgui_init(13.0, nullptr);
	Input::Input::init(m_window);

	m_window->subscribe_event(BIND_FN(App, on_event));
	m_world.init(this);
	m_timer.reset();
	on_init();
}

void App::shutdown() {
	on_shutdown();
	imgui_shutdown();

	m_world.shutdown();
	m_state_machine.transition(StateTransition::quit());
	m_renderer->shutdown();
	m_window->shutdown();

	delete m_renderer;
	delete m_window;
}

bool App::on_window_close(const WindowCloseEvent& event) {
	m_state_machine.transition(StateTransition::quit());
	return true;
}

bool App::on_window_resize(const WindowResizeEvent& event) {
	m_renderer->reset();
	return true;
}
}