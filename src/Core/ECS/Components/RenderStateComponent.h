#pragma once

#include <bgfx/bgfx.h>

namespace Draug {
namespace ECS {
struct RenderStateComponent {
	bgfx::UniformHandle m_light_dir_uniform;
	bgfx::UniformHandle m_camera_pos_uniform;
	int m_state;
};
}
}
