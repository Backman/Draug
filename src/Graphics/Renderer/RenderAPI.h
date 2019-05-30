#pragma once

#if DRAUG_BGFX_RENDERER
#include "impl/bgfx/bgfxRenderAPI.h"
namespace Draug {
class RenderAPI : public impl::bgfxRendererAPI {};
}
#endif
