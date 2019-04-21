#pragma once

#include "Core/Types.h"

namespace Draug {
struct WindowConfig {
	const char* title;
	uint32 pos_x = 0;
	uint32 pos_y = 0;
	uint32 width = 1024;
	uint32 height = 720;
	bool fullscreen = false;

	inline static WindowConfig createWindowed(const char* title, const uint32 pos_x, uint32 pos_y, const uint32 width, const uint32 height) {
		WindowConfig config;
		config.title = title;
		config.pos_x = pos_x;
		config.pos_y = pos_y;
		config.width = width;
		config.height = height;
		config.fullscreen = false;
		return config;
	}

	inline static WindowConfig createFullscreen(const char* title, const uint32 width, const uint32 height) {
		WindowConfig config = createWindowed(title, 0, 0, width, height);
		config.fullscreen = true;
		return config;
	}
};
}
