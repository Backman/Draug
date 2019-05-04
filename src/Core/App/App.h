#pragma once

#include "Draug.h"
#include "State.h"
#include "StateMachine.h"

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
	StateMachine m_state_machine;

private:
	void onEvent(Event& event);
	void initialize();
	void shutdown();
	bool onWindowClose(const WindowCloseEvent& event);

	static App* s_instance;

	Window* m_window;
	Renderer* m_renderer;
};
}
