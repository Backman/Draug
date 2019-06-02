#pragma once

#include "Draug.h"
#include "State.h"
#include "StateMachine.h"
#include "Core/Timer/Timer.h"
#include "Core/ECS/World.h"
#include "Input/Input.h"

namespace Draug {
class Renderer;
class Window;
struct Event;
struct WindowCloseEvent;

class DRAUG_API App {
public:

	App() = default;
	App(const App& other) = default;
	virtual ~App();

	void run();

	inline Window* const get_window() { return m_window; }
	inline Renderer* const get_renderer() { return m_renderer; }

protected:
	virtual void on_init() {}
	virtual void on_shutdown() {}
	ECS::World m_world;
	StateMachine m_state_machine;

	StateContext create_state_context() {
		return { this, &m_world };
	};

private:
	void on_event(Event& event);
	void init();
	void shutdown();
	bool on_window_close(const WindowCloseEvent& event);
	bool on_window_resize(const WindowResizeEvent& event);

	static App* s_instance;

	Window* m_window;
	Renderer* m_renderer;
	Timer m_timer;

	float m_time_scale = 1;
	float m_time;
	float m_unscaled_time;
};
}
