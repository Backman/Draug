#include "Texture.h"
#include "ResourceUtils.h"

namespace Draug {
void Texture::set_data(const bgfx::TextureInfo& info) {
	width = info.width;
	height = info.height;
	format = info.format;
	storage_size = info.storageSize;
}

void Texture::load(bx::FileReaderI& reader, bx::AllocatorI& allocator, const std::string& path) {
	bgfx::TextureInfo info;
	this->path = path;
	handle = load_texture(reader, allocator, path, BGFX_TEXTURE_NONE, &info);
	set_data(info);
}
}