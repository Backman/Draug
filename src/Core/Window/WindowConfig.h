#pragma once

#include "Core/Types.h"

namespace Draug {
	struct WindowConfig {
		const char* title;
		uint32 width;
		uint32 height;
		bool fullscreen;

		static WindowConfig createWindowed(const char* title, const uint32 width, const uint32 height);
		static WindowConfig createFullscreen(const char* title, const uint32 width, const uint32 height);
	};
}
