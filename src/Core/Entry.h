#pragma once

#include "Log/Log.h"
#include "Core/App/App.h"

#if DRAUG_WINDOWS
#define DRAUG_ENTRY(app_class) \
int main(int argc, const char** argv) { \
	Draug::Log::init(); \
	app_class* app = new app_class(); \
	app->run(); \
	delete app; \
	return 0; \
}
#endif
