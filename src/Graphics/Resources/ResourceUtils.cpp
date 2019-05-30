#include "ResourceUtils.h"
#include <bgfx/bgfx.h>

namespace Draug {
bgfx::TextureHandle load_texture(bx::FileReaderI& reader, bx::AllocatorI& allocator, const std::string& path, uint64_t flags, bgfx::TextureInfo* info) {
	return bgfxUtils::load_texture(reader, allocator, path, flags, info);
}
bgfx::TextureHandle load_texture(bx::AllocatorI& allocator, const std::string& name, void* data, uint32_t size, uint64_t flags, bgfx::TextureInfo* info) {
	return bgfxUtils::load_texture(allocator, name, data, size, flags, info);
}
}
