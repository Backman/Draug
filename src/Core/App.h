#pragma once

#include "Draug.h"
#include "AppState.h"
#include "AppStateStack.h"

namespace Draug {
class Window;
struct Event;
struct WindowCloseEvent;

class DRAUG_API App {
public:

	App() = default;
	App(const App& other) = default;
	virtual ~App();

	void run();

	void addState(AppState* state);
	void removeState(AppState* state);

	void addPriorityState(AppState* state);
	void removePriorityState(AppState* state);

	inline Window* getWindow() { return m_window; }

protected:
	virtual void onInitialize() {}
	virtual void onShutdown() {}

private:
	void onEvent(const Event& event);
	void initialize();
	void shutdown();
	bool onWindowClose(const WindowCloseEvent& event);

	static App* s_instance;

	AppStateStack m_states;
	Window* m_window;
	bool m_running = true;
};
}
