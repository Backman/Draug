#pragma once

#include "Draug.h"

namespace Draug {
struct WindowConfig {
	const char* title;
	unsigned int width = 1024;
	unsigned int height = 720;
	bool fullscreen = false;

	inline static WindowConfig create_windowed(const char* title, unsigned int width, unsigned int height) {
		WindowConfig config;
		config.title = title;
		config.width = width;
		config.height = height;
		config.fullscreen = false;
		return config;
	}

	inline static WindowConfig create_fullscreen(const char* title, unsigned int width, unsigned int height) {
		WindowConfig config = create_windowed(title, width, height);
		config.fullscreen = true;
		return config;
	}
};
}
