#include "draugpch.h"
#include "App.h"

namespace Draug {
	App::~App() {
		images.releaseAll();
	}

	void App::initialize() {
	}

	void App::run() {
	}

	void App::shutdown() {

	}
}