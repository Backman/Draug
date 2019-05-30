#pragma once

#include "Draug.h"
#include "ResourceHandle.h"
#include <bgfx/bgfx.h>

namespace Draug {
using TextureHandle = bgfx::TextureHandle;
using TextureInfo = bgfx::TextureInfo;

using ShaderHandle = bgfx::ShaderHandle;
using ProgramHandle = bgfx::ProgramHandle;
using UniformHandle = bgfx::UniformHandle;
using UniformType = bgfx::UniformType::Enum;
using UniformInfo = bgfx::UniformInfo;
}
