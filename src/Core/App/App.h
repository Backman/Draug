#pragma once

#include "Draug.h"
#include "State.h"
#include "Core/World/World.h"
#include "StateMachine.h"
#include "Core/Timer/Timer.h"

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

	inline Window* const getWindow() { return m_window; }
	inline Renderer* const getRenderer() { return m_renderer; }

protected:
	virtual void onInitialize() {}
	virtual void onShutdown() {}
	World m_world;
	StateMachine m_state_machine;

private:
	void onEvent(Event& event);
	void initialize();
	void shutdown();
	bool onWindowClose(const WindowCloseEvent& event);

	static App* s_instance;

	Window* m_window;
	Renderer* m_renderer;
	Timer m_timer;

	float m_time_scale = 1;
	float m_time;
	float m_unscaled_time;
};
}
