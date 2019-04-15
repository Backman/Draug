#include "draugpch.h"
#include "WindowConfig.h"

namespace Draug {
	WindowConfig WindowConfig::createWindowed(const char* title, uint32 width, uint32 height) {
		WindowConfig config;
		config.width = width;
		config.height = width;
		config.title = title;
		config.fullscreen = false;
		return config;
	}

	WindowConfig WindowConfig::createFullscreen(const char* title, uint32 width, uint32 height) {
		WindowConfig config = createWindowed(title, width, height);
		config.fullscreen = true;
		return config;
	}
}

