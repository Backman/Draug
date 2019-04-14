#pragma once

#ifdef DRAUG_PLATFORM_WINDOWS

extern Draug::App* Draug::createApp();

int main(int argc, char** argv) {
	Draug::App* app = Draug::createApp();
	app->initialize();
	app->run();
	app->shutdown();
	delete app;
}

#endif
