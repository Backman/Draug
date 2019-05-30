#include "Texture.h"
#include "ResourceUtils.h"

namespace Draug {
void Texture::load(Texture& texture, bx::FileReaderI* reader, bx::AllocatorI* allocator, const std::string& path) {
	texture.m_path = path;
	texture.m_handle = load_texture(reader, allocator, path, BGFX_TEXTURE_NONE, &texture.m_info);
}
}