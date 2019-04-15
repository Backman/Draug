#pragma once

#include "Core/Core.h"

#ifdef DRAUG_WINDOWS

extern Draug::App* Draug::createApp();

int main(int argc, char** argv) {
	Draug::Log::initialize();

	Draug::App* app = Draug::createApp();
	app->initialize();
	app->run();
	app->shutdown();
	delete app;
}

#endif
