#pragma once

#include "Draug.h"
#include "Resources/ResourceManager.h"

namespace Draug {
class DRAUG_API App {
protected:
	Window m_window;
public:
	App() = default;
	App(const App& other) = default;
	virtual ~App();

	virtual void initialize();
	virtual void run();
	virtual void shutdown();

	inline Window* getWindow() {
		return &m_window;
	};
};

App* createApp();
}
