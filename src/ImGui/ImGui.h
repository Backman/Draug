#pragma once

#include "Draug.h"
#include <bgfx/bgfx.h>
#include <dear-imgui/imgui.h>

namespace bx { struct AllocatorI; }

namespace Draug {
class Window;

void imgui_init(float font_size, bx::AllocatorI* allocator);
void imgui_shutdown();

void imgui_begin_frame(Window* window);
void imgui_end_frame();
}