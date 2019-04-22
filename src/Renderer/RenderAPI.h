#pragma once

#if DRAUG_BGFX_RENDERER
#include "bgfx/bgfxRenderAPI.h"
namespace Draug {
class RenderAPI : public bgfxRendererAPI {};
}
#endif
