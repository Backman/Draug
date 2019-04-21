#pragma once

#include "Draug.h"
#include "Resources/ResourceManager.h"

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

	inline Window* getWindow() { return m_window; }

protected:
	virtual void onInitialize() {}
	virtual void onUpdate() {}
	virtual void onShutdown() {}
	virtual void onEvent(const Event& event);
private:
	void initialize();
	void shutdown();
	bool onWindowClose(const WindowCloseEvent& event);

	static App* s_instance;
	Window* m_window;
	bool m_running = true;
};

App* createApp();
}
