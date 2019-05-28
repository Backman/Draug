#include "App.h"
#include "Renderer/Renderer.h"
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

		imgui_begin_frame(m_window->get_width(), m_window->get_height(), m_window->get_window_id());
		m_renderer->begin_frame();

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
	Event::dispatch<Input::KeyEvent>(event, BIND_STATIC_FN(App, on_key_event));
	Event::dispatch<Input::MouseEvent>(event, BIND_STATIC_FN(App, on_mouse_event));
	m_state_machine.on_event(event);
}

void App::init() {
	s_instance = this;
	WindowConfig window_config = WindowConfig::create_windowed("Draug", 0, 0, 1024, 720);
	m_window = Window::createWindow(window_config);
	m_renderer = new Renderer();
	m_renderer->init(m_window);

	imgui_init(18.0, nullptr);
	Input::Input::init(m_window);

	m_window->subscribe_event(BIND_FN(App, on_event));
	m_world.init(this);
	m_timer.reset();
	on_init();
}

void App::shutdown() {
	on_shutdown();

	m_world.shutdown();
	m_state_machine.transition(StateTransition::quit());
	m_renderer->shutdown();
	m_window->shutdown();
	imgui_shutdown();

	delete m_renderer;
	delete m_window;
}

bool App::on_window_close(const WindowCloseEvent& event) {
	m_state_machine.transition(StateTransition::quit());
	return true;
}

bool App::on_key_event(const Input::KeyEvent& event) {
	ImGuiIO& io = ImGui::GetIO();
	if (event.type == Draug::Input::KeyEvent::Down)
		io.KeysDown[event.key] = true;
	if (event.type == Draug::Input::KeyEvent::Up)
		io.KeysDown[event.key] = false;

	// Modifiers are not reliable across systems
	io.KeyCtrl = io.KeysDown[Draug::Input::Key::LeftControl] || io.KeysDown[Draug::Input::Key::RightControl];
	io.KeyShift = io.KeysDown[Draug::Input::Key::LeftShift] || io.KeysDown[Draug::Input::Key::RightShift];
	io.KeyAlt = io.KeysDown[Draug::Input::Key::LeftAlt] || io.KeysDown[Draug::Input::Key::RightAlt];
	io.KeySuper = io.KeysDown[Draug::Input::Key::LeftSuper] || io.KeysDown[Draug::Input::Key::RightSuper];
	return true;
}

bool App::on_mouse_event(const Input::MouseEvent& event) {
	ImGuiIO& io = ImGui::GetIO();
	switch (event.type) {
		case Draug::Input::MouseEvent::Scroll:
		{
			io.MouseWheelH += (float)event.x_scroll;
			io.MouseWheel += (float)event.y_scroll;
		}
		break;
		default:
			break;
	};
	return true;
}

}