#pragma once

#include <SFML/Window.hpp>
#include "Types.h"

namespace Draug {
struct DisplayConfig {
	const char* title;
	uint32 width;
	uint32 height;
	uint32 pos_x;
	uint32 pos_y;
	bool windowed = true;
};
}

