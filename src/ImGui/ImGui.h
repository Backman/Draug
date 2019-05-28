#pragma once

#include "Draug.h"
#include <bgfx/bgfx.h>
#include <dear-imgui/imgui.h>

namespace bx { struct AllocatorI; }

namespace Draug {
class Window;

#define IMGUI_FLAGS_NONE        UINT8_C(0x00)
#define IMGUI_FLAGS_ALPHA_BLEND UINT8_C(0x01)

void imgui_init(float font_size, bx::AllocatorI* allocator);
void imgui_shutdown();

void imgui_begin_frame(int width, int height, bgfx::ViewId view_id);
void imgui_end_frame();
}