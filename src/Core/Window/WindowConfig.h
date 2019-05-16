#pragma once

#include "Draug.h"

namespace Draug {
struct WindowConfig {
	const char* title;
	int x_pos = 0;
	int y_pos = 0;
	unsigned int width = 1024;
	unsigned int height = 720;
	bool fullscreen = false;

	inline static WindowConfig create_windowed(const char* title, const int x_pos, const int y_pos, const unsigned int width, const unsigned int height) {
		WindowConfig config;
		config.title = title;
		config.x_pos = x_pos;
		config.y_pos = y_pos;
		config.width = width;
		config.height = height;
		config.fullscreen = false;
		return config;
	}

	inline static WindowConfig create_fullscreen(const char* title, const unsigned int width, const unsigned int height) {
		WindowConfig config = create_windowed(title, 0, 0, width, height);
		config.fullscreen = true;
		return config;
	}
};
}
