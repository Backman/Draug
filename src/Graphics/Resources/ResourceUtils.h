#pragma once

#include "Graphics/Renderer/impl/bgfx/bgfxUtils.h"

namespace Draug {
bgfx::TextureHandle load_texture(bx::FileReaderI& reader, bx::AllocatorI& allocator, const std::string& path, uint64_t flags, bgfx::TextureInfo* info);
bgfx::TextureHandle load_texture(bx::AllocatorI& allocator, const std::string& name, void* data, uint32_t size, uint64_t flags, bgfx::TextureInfo* info);
}
